/*完成调用聚合的初始转换*/ 
void transformAggregateCall(ParseState* pstate, Aggref* agg, List* args, List* aggorder, bool agg_distinct)
{
/*链表等一系列变量的定义*/
#define anyenum_typeoid 3500
    List* tlist = NIL; //目标属性
    List* torder = NIL; 
    List* tdistinct = NIL;
    AttrNumber attno = 1;
    int save_next_resno; //下一个分配给目标属性的资源号
    int min_varlevel; //最低级别变量或聚合的级别 
    ListCell* lc = NULL; //创建列表单元，并设置为空
#ifdef PGXC
    HeapTuple aggTuple;
    Form_pg_aggregate aggform;
#endif /* PGXC */

    /*如果为有序集*/
    if (AGGKIND_IS_ORDERED_SET(agg->aggkind)) {
    	/*
		*有序集合aggs包含直接args和聚合args
    	*直接参数保存在第一个“numDirectArgs”参数处，聚集的args位于尾部，必须将它们分开
		*/
        numDirectArgs = list_length(args) - list_length(aggorder); /*计算直接args的数量*/ 
        List* aargs = NIL;
        ListCell* lc1 = NULL; /*创建列表单元*/ 
        ListCell* lc2 = NULL;

        Assert(numDirectArgs >= 0); /*断言直接args的数量不少于0*/ 

        aargs = list_copy_tail(args, numDirectArgs); /*复制列表尾部*/ 
        agg->aggdirectargs = list_truncate(args, numDirectArgs); /*截取掉所有的直接args，获得聚合args*/ 

        /*
		*我们应该保存有序集合agg的排序信息，因此需要构建一个包含聚合参数（Exprs列表）的tlist（通常只有一个目标条目）
		*需要保存用于转换为SortGroupClause的关于顺序的目标
		*/
        forboth(lc1, aargs, lc2, aggorder)
        {
            TargetEntry* tle = makeTargetEntry((Expr*)lfirst(lc1), attno++, NULL, false); /*创建目标条目*/ 
            tlist = lappend(tlist, tle); /*将目标条目tle附加到tlist之后*/ 
            
            /*保存用于转换为SortGroup子句的关于顺序的目标*/
            torder = addTargetToSortList(pstate, tle, torder, tlist, (SortBy*)lfirst(lc2), true); /*修正未知*/ 
        }

        /*断言DISTINCT不能在有序集合agg中使用*/
        Assert(!agg_distinct);
    } else {
    	/*普通的聚合没有直接args*/
        agg->aggdirectargs = NIL;

        /*将Exprs的普通列表转换为目标列表，并且不需要为条目指定列名*/
        foreach (lc, args) {
            Expr* arg = (Expr*)lfirst(lc);
            TargetEntry* tle = makeTargetEntry(arg, attno++, NULL, false); 
            tlist = lappend(tlist, tle);
        }

        /*
		*如果有一个ORDER BY，需要将它转换。
		*如果列出现在ORDER BY中，但不在arg列表中，则会将列添加到tlist
		*它们将被标记为resjunk为真，以便稍后我们可以将它们与常规聚合参数区分开来
		*需要弄乱 p_next_resno，因为它将用于对任何新的目标列表条目进行编号
        *p_next_resno为int类型，表示下一个分配给目标属性的资源号
		*/
        save_next_resno = pstate->p_next_resno;
        pstate->p_next_resno = attno;

        /*转换排序*/ 
        torder = transformSortClause(pstate,
            aggorder,
            &tlist,
            true, /*修正未知*/ 
            true); /*强制执行SQL99规则*/

        /*如果我们有DISTINCT，将其转换为distinctList*/
        if (agg_distinct) {
            tdistinct = transformDistinctClause(pstate, &tlist, torder, true);

			/*如果对聚合散列添加过不同的执行程序支持，则删除此检查*/
            /*遍历tdistinct*/
            foreach (lc, tdistinct) {
                SortGroupClause* sortcl = (SortGroupClause*)lfirst(lc);
                
                /*
                *如果属性所属源表的OID无效，则报告错误信息：不能使用无法识别类型的排序运算符
				*具有DISTINCT的聚合必须能够对其输入进行排序
				*/
                if (!OidIsValid(sortcl->sortop)) {
                    Node* expr = get_sortgroupclause_expr(sortcl, tlist);

                    ereport(ERROR,
                        (errcode(ERRCODE_UNDEFINED_FUNCTION),
                            errmsg(
                                "could not identify an ordering operator for type %s", format_type_be(exprType(expr))),
                            errdetail("Aggregates with DISTINCT must be able to sort their inputs."),
                            parser_errposition(pstate, exprLocation(expr))));
                }
            }
        }

        pstate->p_next_resno = save_next_resno;
    }

    /*使用转换结果更新Aggref*/
    agg->args = tlist;
    agg->aggorder = torder;
    agg->aggdistinct = tdistinct;

    /*聚合的级别与其参数中最低级别变量或聚合的级别相同；或者如果它根本不包含变量，我们假设它是本地的*/
    min_varlevel = find_minimum_var_level((Node*)agg->args);
    /*
	*聚合不能直接包含同一级别的另一个聚合调用（尽管外部aggs可以）
	*如果没有找到任何本地vars或aggs，我们可以跳过此检查
	*SQL规定聚合函数调用不能嵌套
	*/
    if (min_varlevel == 0) {
        if (pstate->p_hasAggs && checkExprHasAggs((Node*)agg->args)) {
            ereport(ERROR,
                (errcode(ERRCODE_GROUPING_ERROR),
                    errmsg("aggregate function calls cannot be nested"),
                    parser_errposition(pstate, locate_agg_of_level((Node*)agg->args, 0))));
        }
    }
    
    /*函数调用不能包含窗口函数调用*/
    if (pstate->p_hasWindowFuncs && checkExprHasWindowFuncs((Node*)agg->args)) {
        ereport(ERROR,
            (errcode(ERRCODE_GROUPING_ERROR),
                errmsg("aggregate function calls cannot contain window function calls"),
                parser_errposition(pstate, locate_windowfunc((Node*)agg->args))));
    }

    if (min_varlevel < 0) {
        min_varlevel = 0;
    }
    agg->agglevelsup = min_varlevel;
    
    /*将正确的pstate标记为具有聚合*/
    while (min_varlevel-- > 0)
        pstate = pstate->parentParseState;
    pstate->p_hasAggs = true;
    /*
	*如果我们在LATERAL进行聚合查询时必须在它的FROM子句中，就说明在此聚合是不适宜的
    *FROM子句中不允许使用聚合
	*/
    if (pstate->p_lateral_active)
        ereport(ERROR,
            (errcode(ERRCODE_GROUPING_ERROR),
             errmsg("aggregates not allowed in FROM clause"),
             parser_errposition(pstate, agg->location)));
#ifdef PGXC
    /*PGXC Datanode聚合的返回数据类型应始终返回transition函数的结果
	*这是Coordinator上的collection函数所期望的
	*查找聚合定义并替换agg->aggtype
	*/
      
    aggTuple = SearchSysCache(AGGFNOID, ObjectIdGetDatum(agg->aggfnoid), 0, 0, 0); /*查找系统缓存*/ 
    if (!HeapTupleIsValid(aggTuple))
        ereport(ERROR,
        	/*报告错误信息：聚合的缓存查找失败*/
            (errcode(ERRCODE_CACHE_LOOKUP_FAILED), errmsg("cache lookup failed for aggregate %u", agg->aggfnoid)));
    aggform = (Form_pg_aggregate)GETSTRUCT(aggTuple);
    agg->aggtrantype = aggform->aggtranstype;
    agg->agghas_collectfn = OidIsValid(aggform->aggcollectfn);
    
    /*
	*当视图包含avg函数时，我们需要确保升级成功
	*否则可能会导致类似错误：operator does not exist:bigint[]=integer
	*例如：create view t1_v as select a from t1 group by a having avg(a) = 10;
	*/
	
	/*对于用户自定义的枚举类型，不要在此处替换agg->aggtype
	*否则可能会导致错误：operator does not exist:operator does not exist: (user-defined enum type) = anyenum;
	*/
    if (IS_PGXC_DATANODE && !isRestoreMode && !u_sess->catalog_cxt.Parse_sql_language && !IsInitdb &&
        !u_sess->attr.attr_common.IsInplaceUpgrade && !IS_SINGLE_NODE && (anyenum_typeoid != agg->aggtrantype))
        agg->aggtype = agg->aggtrantype;

    ReleaseSysCache(aggTuple);
#endif
}

/*完成窗口函数调用的初始转换*/
void transformWindowFuncCall(ParseState* pstate, WindowFunc* wfunc, WindowDef* windef)
{
	/*窗口函数调用不能包含另一个（但aggs可以）*/
    if (pstate->p_hasWindowFuncs && checkExprHasWindowFuncs((Node*)wfunc->args)) {
        ereport(ERROR,
            (errcode(ERRCODE_WINDOWING_ERROR),
                errmsg("window function calls cannot be nested"), /*窗口函数调用不能嵌套*/
                parser_errposition(pstate, locate_windowfunc((Node*)wfunc->args))));
    }

    /*
	*如果OVER子句只指定了一个窗口名，那么查找该WINDOW子句（最好是存在的）
	*否则，请尝试匹配OVER子句的所有属性，并在p_windowdefs中创建一个新条目
    *如果仍未匹配到，就把它全部列出来
	*/
    if (windef->name) {
        Index winref = 0;
        ListCell* lc = NULL;

        AssertEreport(windef->refname == NULL && windef->partitionClause == NIL && windef->orderClause == NIL &&
                          windef->frameOptions == FRAMEOPTION_DEFAULTS,
            MOD_OPT,
            "");

        foreach (lc, pstate->p_windowdefs) {
            WindowDef* refwin = (WindowDef*)lfirst(lc);

            winref++;
            if (refwin->name && strcmp(refwin->name, windef->name) == 0) {
                wfunc->winref = winref;
                break;
            }
        }
        if (lc == NULL) { /*未找到 window子句*/
            ereport(ERROR,
                (errcode(ERRCODE_UNDEFINED_OBJECT),
                    errmsg("window \"%s\" does not exist", windef->name), /*窗口不存在*/
                    parser_errposition(pstate, windef->location)));
        }
    } else {
        Index winref = 0;
        ListCell* lc = NULL;

        foreach (lc, pstate->p_windowdefs) {
            WindowDef* refwin = (WindowDef*)lfirst(lc);

            winref++;
            if (refwin->refname && windef->refname && strcmp(refwin->refname, windef->refname) == 0); /*匹配refname*/
            else if (!refwin->refname && !windef->refname); /*没有匹配到refname*/
            else
                continue;
            if (equal(refwin->partitionClause, windef->partitionClause) &&
                equal(refwin->orderClause, windef->orderClause) && refwin->frameOptions == windef->frameOptions &&
                equal(refwin->startOffset, windef->startOffset) && equal(refwin->endOffset, windef->endOffset)) {
                /*发现重复的窗口规范*/
                wfunc->winref = winref;
                break;
            }
        }

        /*未找到 over子句属性*/
        if (lc == NULL) {
            pstate->p_windowdefs = lappend(pstate->p_windowdefs, windef);
            wfunc->winref = list_length(pstate->p_windowdefs);
        }
    }

    pstate->p_hasWindowFuncs = true;
}

/*分析和检查，并找出使用有误的聚合函数*/ 
void parseCheckAggregates(ParseState* pstate, Query* qry)
{
	/*链表等一系列变量的定义*/
    List* gset_common = NIL; /*创建交集*/ 
    List* groupClauses = NIL; /*GROUP BY子句*/ 
    List* groupClauseCommonVars = NIL; 
    bool have_non_var_grouping = false; /*用于判断是否存在非变量分组集*/
    List* func_grouped_rels = NIL;
    ListCell* l = NULL; /*创建一个列表单元*/ 
    bool hasJoinRTEs = false; /*用于判断是否存在RTE_JOIN*/ 
    bool hasSelfRefRTEs = false; /*用于判断是否存在自引用CTE条目*/ 
    PlannerInfo* root = NULL; /*创建一个根结点*/ 
    Node* clause = NULL;
    
    /*只有在发现聚合或分组时才调用此函数*/
    AssertEreport(pstate->p_hasAggs || qry->groupClause || qry->havingQual || qry->groupingSets,
        MOD_OPT,
        "only be called if we found aggregates or grouping");
        
    /*如果已经生成了分组集，则展开它们并找到所有集合的交集*/
    if (qry->groupingSets) {
    	/*4096并没有什么特别的含义，4096只是一种限制，数值是任意的，只是为了避免病态构造带来的资源问题*/ 
        List* gsets = expand_grouping_sets(qry->groupingSets, 4096);

        if (gsets == NULL) /*如果集合为空，报告错误信息*/ 
            ereport(ERROR,
                (errcode(ERRCODE_STATEMENT_TOO_COMPLEX), /*显示错误代码*/ 
                    errmsg("too many grouping sets present (max 4096)"), /*报告错误信息*/ 
                    /*判断分析器错误位置*/ 
                    parser_errposition(pstate,
                        qry->groupClause ? exprLocation((Node*)qry->groupClause)
                                         : exprLocation((Node*)qry->groupingSets))));                          
        /*交集通常是空的，因此通过设置最小集合来获得交集，以提高解决问题的效率*/ 
        gset_common = (List*)linitial(gsets);

        /*如果交集不为空，则遍历所有分组集*/ 
        if (gset_common != NULL) {
            for_each_cell(l, lnext(list_head(gsets))) {
            	/*
				*用交集与分组集形成新的交集
				*再用上一次循环中获得的新交集与另一分组集形成新的交集 
				*/ 
                gset_common = list_intersection_int(gset_common, (List*)lfirst(l));
                /*直到交集为空或者遍历完所有分组集为止，结束循环并继续向下进行*/ 
                if (gset_common == NULL) {
                    break;
                }
            }
        }
        /*
		*如果扩展中只有一个分组集，并且groupClause为非空（这意味着分组集也不是空的）
		*那么我们可以舍弃分组集，并假设只有一个正常的GROUP BY
		*/
        if (list_length(gsets) == 1 && qry->groupClause) {
            qry->groupingSets = NIL;
        }
    }
    /*扫描范围表以查看是否存在连接（JOIN）或者自引用CTE条目*/ 
    hasJoinRTEs = hasSelfRefRTEs = false;
    foreach (l, pstate->p_rtable) {
        RangeTblEntry* rte = (RangeTblEntry*)lfirst(l);

        if (rte->rtekind == RTE_JOIN) {
            hasJoinRTEs = true;
        } else if (rte->rtekind == RTE_CTE && rte->self_reference) {
            hasSelfRefRTEs = true;
        }
    }
    
    /*
	*聚合不得出现在WHERE或JOIN/ON子句中。
	*此检查应首先出现，以传递适当的错误消息；否则，可能会将错误归结于目标列表中的某个无辜变量
	*如果问题在WHERE语句中，可能会产生误导
	*/
    if (checkExprHasAggs(qry->jointree->quals)) {
        ereport(ERROR,
            (errcode(ERRCODE_GROUPING_ERROR),
                errmsg("aggregates not allowed in WHERE clause"),
                parser_errposition(pstate, locate_agg_of_level(qry->jointree->quals, 0))));
    }
    if (checkExprHasAggs((Node*)qry->jointree->fromlist)) { 
        ereport(ERROR,
            (errcode(ERRCODE_GROUPING_ERROR),
                errmsg("aggregates not allowed in JOIN conditions"),
                parser_errposition(pstate, locate_agg_of_level((Node*)qry->jointree->fromlist, 0))));
    }
    
    /*
	*GROUP BY子句中也不允许使用聚合
	*当进行此操作时，构建一个可接受的GROUP BY表达式列表，供check_ungrouped_columns()（用于检查未分组的列）使用
	*/	
	/*遍历分组集的子集*/ 
    foreach (l, qry->groupClause) {
        SortGroupClause* grpcl = (SortGroupClause*)lfirst(l);
        TargetEntry* expr = NULL;  /*创建目标条目，用于获取目标列表*/

        expr = get_sortgroupclause_tle(grpcl, qry->targetList); /*找到匹配grpc1的目标列表并传递给expr*/ 
         /*
		 *如果expr为空，则不执行下一个if语句，直接进入下一次循环
		 *也就是说，直到找到目标列表或者遍历完所有子集为止 
		 */ 
        if (expr == NULL) {
            continue; 
        }
        if (checkExprHasAggs((Node*)expr->expr)) {
            ereport(ERROR,
                (errcode(ERRCODE_GROUPING_ERROR),
                    errmsg("aggregates not allowed in GROUP BY clause"),
                    parser_errposition(pstate, locate_agg_of_level((Node*)expr->expr, 0))));
        }
        groupClauses = lcons(expr, groupClauses);
    }
    
    /*
	*如果涉及到连接别名变量，必须将它们展平到基础变量，以便正确地将别名变量和非别名变量视为相等
	*如果范围表条目中都不存在RTE_JOIN，便可以跳过这个步骤
	*使用planner的flatten_join_alias_vars例程对其进行展平
	*它需要一个PlannerInfo根节点，大部分是可以虚拟的
	*/
    if (hasJoinRTEs) {
        root = makeNode(PlannerInfo);
        root->parse = qry;
        root->planner_cxt = CurrentMemoryContext;
        root->hasJoinRTEs = true;

        groupClauses = (List*)flatten_join_alias_vars(root, (Node*)groupClauses);
    } else
        root = NULL; /*如果都不存在RTE_JOIN，则不执行上一个if当中的语句*/ 
    
    /*
	*检测所有分组表达式，如果都是Vars，那么就不必在递归扫描中耗费大量精力
	*在展平别名后，在groupClauseCommonVars中分别跟踪所有分组集中包含的变量
	*因为这些变量是唯一可以用来检查函数相关性的变量
	*/
    have_non_var_grouping = false;
    foreach (l, groupClauses) {
        TargetEntry* tle = (TargetEntry*)lfirst(l);
        if (!IsA(tle->expr, Var)) { /*如果有一个分组表达式不是 Var*/ 
            have_non_var_grouping = true;
        } else if (!qry->groupingSets || list_member_int(gset_common, tle->ressortgroupref)) {
        	/*否则，将tle->expr附加在groupClauseCommonVars之后*/ 
            groupClauseCommonVars = lappend(groupClauseCommonVars, tle->expr);
        }
    }
    
    /*
	*检查目标列表和HAVING子句中未分组的变量
	*检查resjunk tlist元素以及常规元素，会找到来自ORDER BY和WINDOW子句的未分组变量
	*还将检查分组表达式本身（都会通过测试）
	*最终确定分组表达式，为此需要遍历原始（未展平）子句以修改节点
	*/
    clause = (Node*)qry->targetList;
    finalize_grouping_exprs(clause, pstate, qry, groupClauses, root, have_non_var_grouping);
	/* 如果存在RTE_JOIN则展平*/
	if (hasJoinRTEs) {
        clause = flatten_join_alias_vars(root, clause);
    }
    /*检查未分组的列*/ 
    check_ungrouped_columns(
        clause, pstate, qry, groupClauses, groupClauseCommonVars, have_non_var_grouping, &func_grouped_rels);

    clause = (Node*)qry->havingQual;
    finalize_grouping_exprs(clause, pstate, qry, groupClauses, root, have_non_var_grouping);
    if (hasJoinRTEs) {
        clause = flatten_join_alias_vars(root, clause);
    }
    check_ungrouped_columns(
        clause, pstate, qry, groupClauses, groupClauseCommonVars, have_non_var_grouping, &func_grouped_rels);
    
    /*根据规范，聚合不能出现在递归项中。*/
    if (pstate->p_hasAggs && hasSelfRefRTEs) {
        ereport(ERROR,
            (errcode(ERRCODE_INVALID_RECURSION),
                errmsg("aggregate functions not allowed in a recursive query's recursive term"),
                parser_errposition(pstate, locate_agg_of_level((Node*)qry, 0))));
    }
}

/*解析检查，并找出使用有误的窗口函数*/ 
void parseCheckWindowFuncs(ParseState* pstate, Query* qry)
{
    ListCell* l = NULL;

    /*只有在检测到窗口函数时才调用此函数*/ 
    AssertEreport(pstate->p_hasWindowFuncs, MOD_OPT, "Only deal with WindowFuncs here");

    /*WHERE子句中不允许使用窗口函数*/ 
    if (checkExprHasWindowFuncs(qry->jointree->quals)) {
        ereport(ERROR,
            (errcode(ERRCODE_WINDOWING_ERROR),
                errmsg("window functions not allowed in WHERE clause"),
                parser_errposition(pstate, locate_windowfunc(qry->jointree->quals))));
    }
    /*连接条件(JOIN)中不允许使用窗口函数*/ 
    if (checkExprHasWindowFuncs((Node*)qry->jointree->fromlist)) {
        ereport(ERROR,
            (errcode(ERRCODE_WINDOWING_ERROR),
                errmsg("window functions not allowed in JOIN conditions"),
                parser_errposition(pstate, locate_windowfunc((Node*)qry->jointree->fromlist))));
    }
    /*HAVING子句中不允许使用窗口函数*/ 
    if (checkExprHasWindowFuncs(qry->havingQual)) {
        ereport(ERROR,
            (errcode(ERRCODE_WINDOWING_ERROR),
                errmsg("window functions not allowed in HAVING clause"),
                parser_errposition(pstate, locate_windowfunc(qry->havingQual))));
    }
    
    /*GROUP BY子句中不允许使用窗口函数*/
    /*遍历groupClause*/ 
    foreach (l, qry->groupClause) {
        SortGroupClause* grpcl = (SortGroupClause*)lfirst(l);
        Node* expr = NULL;

        expr = get_sortgroupclause_expr(grpcl, qry->targetList);
        if (checkExprHasWindowFuncs(expr)) {
            ereport(ERROR,
                (errcode(ERRCODE_WINDOWING_ERROR),
                    errmsg("window functions not allowed in GROUP BY clause"),
                    parser_errposition(pstate, locate_windowfunc(expr))));
        }
    }

    /*窗口定义中不允许使用窗口函数*/
    /*检查window specifications的表达式中是否包含当前查询级别的窗口函数调用 */
    /*遍历 windowClause*/
    foreach (l, qry->windowClause) {
        WindowClause* wc = (WindowClause*)lfirst(l);
        ListCell* l2 = NULL;

        foreach (l2, wc->partitionClause) {
            SortGroupClause* grpcl = (SortGroupClause*)lfirst(l2);
            Node* expr = NULL;

            expr = get_sortgroupclause_expr(grpcl, qry->targetList);
            if (checkExprHasWindowFuncs(expr)) {
                ereport(ERROR,
                    (errcode(ERRCODE_WINDOWING_ERROR),
                        errmsg("window functions not allowed in window definition"),
                        parser_errposition(pstate, locate_windowfunc(expr))));
            }
        }
        /*遍历 orderClause*/
        foreach (l2, wc->orderClause) {
            SortGroupClause* grpcl = (SortGroupClause*)lfirst(l2);
            Node* expr = NULL;

            expr = get_sortgroupclause_expr(grpcl, qry->targetList); /*查询与grpcl匹配的目标列表*/
            if (checkExprHasWindowFuncs(expr)) {
                ereport(ERROR,
                    (errcode(ERRCODE_WINDOWING_ERROR),
                        errmsg("window functions not allowed in window definition"),
                        parser_errposition(pstate, locate_windowfunc(expr))));
            }
        }
        /*已在transformFrameOffset中检查startOffset和limitOffset*/
    }
}

static void check_ungrouped_columns(Node* node, ParseState* pstate, Query* qry, List* groupClauses,
    List* groupClauseCommonVars, bool have_non_var_grouping, List** func_grouped_rels)
{
    check_ungrouped_columns_context context;

    /*将给定表达式树中的数据传递给 context*/
    context.pstate = pstate; //当前解析状态
    context.qry = qry; //原始解析查询树
    context.root = NULL; //规划、优化信息根结点
    context.groupClauses = groupClauses; //group子句
    context.groupClauseCommonVars = groupClauseCommonVars;
    context.have_non_var_grouping = have_non_var_grouping; //判断是否含有未分组变量
    context.func_grouped_rels = func_grouped_rels; 
    context.sublevels_up = 0;
    context.in_agg_direct_args = false;  //设定in_agg_direct_args的初始值为false
    /*调用 check_ungrouped_columns_walker() 扫描给定表达式树中的未分组变量*/
    (void)check_ungrouped_columns_walker(node, &context);
}

static bool check_ungrouped_columns_walker(Node* node, check_ungrouped_columns_context* context)
{
    ListCell* gl = NULL;

    /*如果节点为空，则返回 false*/ 
    if (node == NULL) {
        return false;
    }
    /*如果节点类型为 Const 或者 Param，则返回 false*/ 
    if (IsA(node, Const) || IsA(node, Param)) {
        return false; /*常数总是可以接受的*/
    }

    /*如果节点类型为 Aggref*/ 
    if (IsA(node, Aggref)) {
        Aggref* agg = (Aggref*)node;

        /*如果找到与 context->sublevels_up 相同级别的聚合调用*/ 
        if ((int)agg->agglevelsup == context->sublevels_up) {
        	/*对于有序集合agg，其直接参数不应位于聚合内。
			 *如果我们找到原始级别的聚合调用（如果它在外部查询中，context应该是相同的）
			 *不要递归到它的普通参数、ORDER BY参数或filter过滤器中；未分组变量没有错误。
			 *我们在上下文中使用in_agg_direct_args来帮助为直接参数中的未分组变量生成有用的错误消息。
			 */
            bool result = false; /*标记返回值为 false*/ 

            /*如果有序集合 agg 内含有直接参数，则报告错误信息*/ 
            if (context->in_agg_direct_args) {
                ereport(ERROR, (errcode(ERRCODE_INVALID_AGG), errmsg("unexpected args inside agg direct args")));
            }
            context->in_agg_direct_args = true;
            result = check_ungrouped_columns_walker((Node*)agg->aggdirectargs, context); /*递归*/ 
            context->in_agg_direct_args = false; /*恢复设定的初始值 false，保证下一次调用正常*/ 
            return result;
        }

        /*
         *我们也可以跳过更高级别聚合的参数，因为它们不可能包含我们关心的变量（参见transformAggregateCall）。
         *因此，我们只需要研究较低层次聚合的参数。
         */
        if ((int)agg->agglevelsup > context->sublevels_up) {
            return false;
        }
    }

    /*如果 node 节点类型为 GroupingFunc*/
    if (IsA(node, GroupingFunc)) {
        GroupingFunc* grp = (GroupingFunc*)node;

        /*单独处理 GroupingFunc，此级别无需重新检查*/
        if ((int)grp->agglevelsup >= context->sublevels_up) {
            return false;
        }
    }
    /*如果我们有任何不是简单变量的 GROUP BY 项，请检查子表达式作为一个整体是否匹配任何GROUP BY项。
	 *我们需要在每个递归级别执行此操作，以便在到达 GROUPed-BY 表达式之前识别它们。
	 *但是这仅适用于外部查询级别。
     */
    if (context->have_non_var_grouping && context->sublevels_up == 0) {
        foreach (gl, context->groupClauses) {
            TargetEntry* tle = (TargetEntry*)lfirst(gl);
            //如果子表达式与 node 匹配，返回 false，此时已完成，无需继续循环
            if (equal(node, tle->expr)) {
                return false; 
            }
        }
    }

#ifndef ENABLE_MULTIPLE_NODES
    /*如果存在 ROWNUM，则它必须出现在 GROUP BY 子句中或用于聚合函数*/
    if (IsA(node, Rownum)) {
        find_rownum_in_groupby_clauses((Rownum *)node, context);
    }
#endif
    /*如果有原始查询级别的未分组变量，则出现问题（来自原始查询级别以下或以上的变量无关紧要）。*/
    /*如果 node 节点类型为Var*/ 
    if (IsA(node, Var)) {
        Var* var = (Var*)node;
        RangeTblEntry* rte = NULL;
        char* attname = NULL;

        if (var->varlevelsup != (unsigned int)context->sublevels_up) {
            return false;  /*如果不是原始查询级别则没有问题*/ 
        }

        /* 如果没有进行上面的匹配，执行以下代码*/
        if (!context->have_non_var_grouping || context->sublevels_up != 0) {
            foreach (gl, context->groupClauses) {
                Var* gvar = (Var*)((TargetEntry*)lfirst(gl))->expr;

                if (IsA(gvar, Var) && gvar->varno == var->varno && gvar->varattno == var->varattno &&
                    gvar->varlevelsup == 0)
                    return false; 
            }
        }
 
        /*检查变量是否在功能上依赖于 GROUP BY 列。
		 *如果是这样的话，我们可以允许使用Var，因为对于这个表来说，分组实际上是一个空操作。
         *但是，这种推断取决于表的一个或多个约束，因此我们必须将这些约束添加到查询的 constraintDeps 列表中。
         *因为如果删除了约束，它在语义上不再有效。
         *因此，在引发错误之前，这将是最后一次检查，如果不成功，还需要添加依赖项
         *
         *因为这是一个非常耗时的检查，并且对于表的所有列都会有相同的结果，所以在 func_grouped_rels 列表中证明了一些RTE的依赖关系。
		 *此测试还防止我们向constraintDeps列表中添加重复条目。*/
        if (list_member_int(*context->func_grouped_rels, var->varno)) {
            return false; 
        }

        /*断言*/
        AssertEreport(
            var->varno > 0 && (int)var->varno <= list_length(context->pstate->p_rtable), MOD_OPT, "Var is unexpected");
        rte = rt_fetch(var->varno, context->pstate->p_rtable);
        if (rte->rtekind == RTE_RELATION) {
            if (check_functional_grouping(
                    rte->relid, var->varno, 0, context->groupClauseCommonVars, &context->qry->constraintDeps)) {
                *context->func_grouped_rels = lappend_int(*context->func_grouped_rels, var->varno);
                return false; 
            }
        }

        /*如果找到未分组的局部变量，生成错误信息*/
        attname = get_rte_attribute_name(rte, var->varattno);

        /*如果RTE被重写，则修改attname*/
        char* orig_attname = attname; //拷贝一份原始的attname
        //如果RTE被重写
        if (IsSWCBRewriteRTE(rte)) {
            attname = strrchr(attname, '@'); //在 attname 所指向的字符串中搜索最后一次出现字符 @ 的位置
            attname = (attname != NULL) ? (attname + 1) : orig_attname;//如果不为空则向后移动1个字符，否则恢复原来的attname
        }
        
        /*错误信息报告*/
        if (context->sublevels_up == 0) {
            ereport(ERROR,
                (errcode(ERRCODE_GROUPING_ERROR),
                    errmsg("column \"%s.%s\" must appear in the GROUP BY clause or be used in an aggregate function",
                        rte->eref->aliasname,
                        attname),
                    context->in_agg_direct_args
                        ? errdetail("Direct arguments of an ordered-set aggregate must use only grouped columns.")
                        : 0,
                    rte->swConverted ? errdetail("Please check your start with rewrite table's column.") : 0,
                    parser_errposition(context->pstate, var->location)));
        } else {
            ereport(ERROR,
                (errcode(ERRCODE_GROUPING_ERROR),
                    errmsg("subquery uses ungrouped column \"%s.%s\" from outer query", rte->eref->aliasname, attname),
                    parser_errposition(context->pstate, var->location)));
        }
        if (attname != NULL) {
            pfree_ext(attname);
        }
    }
 
    /*如果 node 节点类型为 Query*/ 
    if (IsA(node, Query)) {
    	/*递归到子选择中*/
        bool result = false;

        context->sublevels_up++;
        result = query_tree_walker((Query*)node, (bool (*)())check_ungrouped_columns_walker, (void*)context, 0);
        context->sublevels_up--;
        return result;
    }
    /*返回表达式树*/ 
    return expression_tree_walker(node, (bool (*)())check_ungrouped_columns_walker, (void*)context);
}

static void finalize_grouping_exprs(
    Node* node, ParseState* pstate, Query* qry, List* groupClauses, PlannerInfo* root, bool have_non_var_grouping)
{
    check_ungrouped_columns_context context;

    /*将给定表达式树中的数据传递给 context*/
    context.pstate = pstate; //当前解析状态
    context.qry = qry; //原始解析查询树
    context.root = root; //规划、优化信息根结点
    context.groupClauses = groupClauses; //group子句
    context.groupClauseCommonVars = NIL;
    context.have_non_var_grouping = have_non_var_grouping; //判断是否含有未分组变量
    context.func_grouped_rels = NULL;

    context.sublevels_up = 0;
    context.in_agg_direct_args = false;  //设定in_agg_direct_args的初始值为false
    /* 调用 finalize_grouping_exprs_walkerGROUPING() 扫描给定表达式树中的 GROUPING() 和相关调用 */
    (void)finalize_grouping_exprs_walker(node, &context);
}

static bool finalize_grouping_exprs_walker(Node* node, check_ungrouped_columns_context* context)
{
    ListCell* gl = NULL;

    /*如果节点为空，则返回 false*/
    if (node == NULL) {
        return false;
    }
    /*如果节点类型为 Const 或者 Param，则返回 false*/
    if (IsA(node, Const) || IsA(node, Param)) {
        return false; /*常数总是可以接受的*/
    }

    /*如果节点类型为 Aggref*/
    if (IsA(node, Aggref)) {
        Aggref* agg = (Aggref*)node;

        /*如果找到与 context->sublevels_up 相同级别的聚合调用*/
        if ((int)agg->agglevelsup == context->sublevels_up) {
        	/*
             *如果我们找到原始级别的聚合调用，不要递归到它的普通参数、ORDER BY 参数或filter过滤器中；
			 *此处不允许使用此级别的GROUPING表达式。但检查直接参数时，就当作它们未聚合
             */
            bool result = false;

            AssertEreport(!context->in_agg_direct_args, MOD_OPT, "");
            context->in_agg_direct_args = true;
            result = finalize_grouping_exprs_walker((Node*)agg->aggdirectargs, context); /*递归*/
            context->in_agg_direct_args = false; /*恢复设定的初始值 false，保证下一次调用正常*/
            return result;
        }

        /*
        *我们也可以跳过更高级别聚合的参数，因为它们不可能包含我们关心的变量（参见transformAggregateCall）。
        *因此，我们只需要研究较低层次聚合的参数。
        */
        if ((int)agg->agglevelsup > context->sublevels_up) {
            return false;
        }
    }

    /*如果 node 节点类型为 GroupingFunc*/
    if (IsA(node, GroupingFunc)) {
        GroupingFunc* grp = (GroupingFunc*)node;

        /* 只需要在其所属的级别检查 GroupingFunc 节点，因为它们不能在参数中混合级别*/
        if ((int)grp->agglevelsup == context->sublevels_up) {
            ListCell* lc = NULL;
            List* ref_list = NIL;

            foreach (lc, grp->args) {
                Node* expr = (Node*)lfirst(lc);
                Index ref = 0;

                //如果根结点不为空，则展平表达式
                if (context->root != NULL) {
                    expr = flatten_join_alias_vars(context->root, expr);
                }

                /*每个表达式必须与当前查询级别的分组项匹配。与一般表达式不同，不允许函数依赖或外部引用。*/
                if (IsA(expr, Var)) {
                    Var* var = (Var*)expr;

                    /* 如果 var 与 context 查询级别相同 */
                    if ((int)var->varlevelsup == context->sublevels_up) {
                        foreach (gl, context->groupClauses) {
                            TargetEntry* tle = (TargetEntry*)lfirst(gl);
                            Var* gvar = (Var*)tle->expr;

                            if (IsA(gvar, Var) && gvar->varno == var->varno && gvar->varattno == var->varattno &&
                                gvar->varlevelsup == 0) {
                                ref = tle->ressortgroupref;
                                break;
                            }
                        }
                    }
                } else if (context->have_non_var_grouping && context->sublevels_up == 0) {
                    foreach (gl, context->groupClauses) {
                        TargetEntry* tle = (TargetEntry*)lfirst(gl);

                        if (equal(expr, tle->expr)) {
                            ref = tle->ressortgroupref;
                            break;
                        }
                    }
                }
     
                /*GROUPING 的参数必须是关联查询级别的分组表达式*/ 
                if (ref == 0) {
                    ereport(ERROR,
                        (errcode(ERRCODE_GROUPING_ERROR),
                            errmsg("arguments to GROUPING must be grouping expressions of the associated query level"),
                            parser_errposition(context->pstate, exprLocation(expr))));
                }

                ref_list = lappend_int(ref_list, ref);
            }

            grp->refs = ref_list;
        }

        /*如果高于当前查询级别，则返回false*/
        if ((int)grp->agglevelsup > context->sublevels_up) {
            return false;
        }
    }

    /*如果 node 节点为 Query 类型 */
    if (IsA(node, Query)) {
        /*递归到子选择中*/
        bool result = false;

        context->sublevels_up++;
        result = query_tree_walker((Query*)node, (bool (*)())finalize_grouping_exprs_walker, (void*)context, 0);
        context->sublevels_up--;
        return result;
    }
    /*返回表达式查询树*/
    return expression_tree_walker(node, (bool (*)())finalize_grouping_exprs_walker, (void*)context);
}

/*
 *expand_groupingset_node 负责展开不同类型的节点
 *给定一个 GroupingSet 节点，将其展开并返回一个嵌套链表（储存链表的链表）。
 *对于 EMPTY 节点，返回一个储存空链表的链表。
 *对于 SIMPLE 节点，返回一个储存节点内容的链表。
 *对于 CUBE 和 ROLLUP 节点，返回拓展列表。
 *对于 SET 节点，递归拓展包含的 CUBE 和 ROLLUP 节点。
 */
static List* expand_groupingset_node(GroupingSet* gs)
{
    List* result = NIL;

    /*检测节点类型*/
    switch (gs->kind) {
        case GROUPING_SET_EMPTY:
            result = list_make1(NIL);
            break;

        case GROUPING_SET_SIMPLE:
            result = list_make1(gs->content);
            break;

        case GROUPING_SET_ROLLUP: {
            List* rollup_val = gs->content;
            ListCell* lc = NULL;
            int curgroup_size = list_length(gs->content);

            while (curgroup_size > 0) {
                List* current_result = NIL;
                int i = curgroup_size;

                /*遍历储存节点内容的链表*/
                foreach (lc, rollup_val) {
                    GroupingSet* gs_current = (GroupingSet*)lfirst(lc);

                    /*种类出乎意料*/
                    AssertEreport(gs_current->kind == GROUPING_SET_SIMPLE, MOD_OPT, "Kind is unexpected");

                    /*将当前链表与储存节点内容的链表连接*/
                    current_result = list_concat(current_result, list_copy(gs_current->content));

                    /*如果完成了当前组的创建，结束循环*/
                    /* If we are done with making the current group, break */
                    if (--i == 0) {
                        break;
                    }
                }

                /*将连接后获得的链表拼接到 result 链表*/
                result = lappend(result, current_result);
                --curgroup_size;
            }

            result = lappend(result, NIL);
        } break;

        case GROUPING_SET_CUBE: {
            List* cube_list = gs->content;
            int number_bits = list_length(cube_list);
            uint32 num_sets;
            uint32 i;

            /*解析器的上限应该低得多*/
            /* parser should cap this much lower */
            AssertEreport(number_bits < 31, MOD_OPT, "parser should cap this much lower");

            num_sets = (1U << (unsigned int)number_bits);

            for (i = 0; i < num_sets; i++) {
                List* current_result = NIL;
                ListCell* lc = NULL;
                uint32 mask = 1U;


                foreach (lc, cube_list) {
                    GroupingSet* gs_current = (GroupingSet*)lfirst(lc);

                    /*种类出乎意料*/
                    AssertEreport(gs_current->kind == GROUPING_SET_SIMPLE, MOD_OPT, "Kind is unexpected");

                    if (mask & i) {
                        current_result = list_concat(current_result, list_copy(gs_current->content));
                    }

                    //mask扩大为原来的二倍
                    mask <<= 1;
                }

                /*将所得链表拼接到 result 链表*/
                result = lappend(result, current_result);
            }
        } break;

        case GROUPING_SET_SETS: {
            ListCell* lc = NULL;

            foreach (lc, gs->content) {
                /*使用递归拓展包含的 CUBE 和 ROLLUP 节点*/
                List* current_result = expand_groupingset_node((GroupingSet*)lfirst(lc));

                result = list_concat(result, current_result);
            }
        } break;
        default:
            break;
    }

    return result;
}

/* 比较两个链表长度是否相等 */
static int cmp_list_len_asc(const void* a, const void* b)
{
    int la = list_length(*(List* const*)a);
    int lb = list_length(*(List* const*)b);

    return (la > lb) ? 1 : (la == lb) ? 0 : -1;
}


/*
 *为聚合的转换和最终函数创建表达式树。
 *这些都是必需的，这样多态函数就可以在聚合中使用——如果没有表达式树，这些函数就不会知道它们应该使用的数据类型。
 *（然而，这些树永远不会被执行，所以我们可以略过一些正确性。）
 * 
 *agg_input_types, agg_state_type,和agg_result_type标识聚合的输入、转换和结果类型。
 *这些都应该解析为实际类型（例如，任何类型都不应该是ANYELEMENT等）
 *agginput_collation是聚合函数的输入排序规则。
 * 
 *transfnoid和finalfnoid标识要调用的函数；后者可能是InvalidOid。
 * 
 *指向构造树的指针将返回到*transnexpr和*finalfnexpr。如果没有finalf，则后者设置为NULL
 */
void build_aggregate_fnexprs(Oid* agg_input_types, int agg_num_inputs, Oid agg_state_type, Oid agg_result_type,
    Oid agg_input_collation, Oid transfn_oid, Oid finalfn_oid, Expr** transfnexpr, Expr** finalfnexpr)
{
    Param* argp = NULL;
    List* args = NIL;
    int i;

    /*
     *构建要在transfn FuncExpr节点中使用的参数列表。
     *我们只关心transfn可以在运行时使用get_fn_expr_argtype（）发现实际的参数类型，所以可以使用与任何实际Param都不对应的Param节点。
     */
    argp = makeNode(Param);
    argp->paramkind = PARAM_EXEC;/*运行时发现的实际参数类型*/
    argp->paramid = -1;
    argp->paramtype = agg_state_type; /*标识聚合的转换类型*/
    argp->paramtypmod = -1;
    argp->paramcollid = agg_input_collation; /*聚合输入的排序规则*/
    argp->location = -1; 

    args = list_make1(argp);

    for (i = 0; i < agg_num_inputs; i++) {
        argp = makeNode(Param);
        argp->paramkind = PARAM_EXEC;
        argp->paramid = -1;
        argp->paramtype = agg_input_types[i];/*标识聚合的输入类型*/
        argp->paramtypmod = -1;
        argp->paramcollid = agg_input_collation;
        argp->location = -1;
        args = lappend(args, argp);
    }

    *transfnexpr =
        (Expr*)makeFuncExpr(transfn_oid, agg_state_type, args, InvalidOid, agg_input_collation, COERCE_DONTCARE);

    /*如果没有最后一个函数，将*finalfnexpr设置为NULL*/
    if (!OidIsValid(finalfn_oid)) {
        *finalfnexpr = NULL;
        return;
    }

    /*为最终函数构建表达式树*/
    argp = makeNode(Param);
    argp->paramkind = PARAM_EXEC;
    argp->paramid = -1;
    argp->paramtype = agg_state_type;
    argp->paramtypmod = -1;
    argp->paramcollid = agg_input_collation;
    argp->location = -1;
    args = list_make1(argp);

    *finalfnexpr =
        (Expr*)makeFuncExpr(finalfn_oid, agg_result_type, args, InvalidOid, agg_input_collation, COERCE_DONTCARE);
}

/*
 *为聚合的转换和最终函数创建表达式树。
 *这些都是必需的，这样多态函数就可以在聚合中使用——如果没有表达式树，这些函数就不会知道它们应该使用的数据类型。
 *（然而，这些树永远不会被执行，所以我们可以略过一些正确性。）
 * 
 *agg_input_types, agg_state_type和agg_result_type标识聚合的输入、转换和结果类型。
 *这些都应该解析为实际类型（例如，任何类型都不应该是ANYELEMENT等）。
 *agginput_collation是聚合函数的输入排序规则。
 * 
 *对于有序集聚合，请记住agg_input_types描述了聚合参数后面的直接参数。
 * 
 *transfnoid和finalfnoid标识要调用的函数；后者可能是InvalidOid
 * 
 *指向构造树的指针将返回到*transnexpr和*finalfnexpr。如果没有finalfn，则后者设置为NULL。
 */
void build_trans_aggregate_fnexprs(int agg_num_inputs, int agg_num_direct_inputs, bool agg_ordered_set,
    bool agg_variadic, Oid agg_state_type, Oid* agg_input_types, Oid agg_result_type, Oid agg_input_collation,
    Oid transfn_oid, Oid finalfn_oid, Expr** transfnexpr, Expr** finalfnexpr)
{
    Param* argp = NULL;
    List* args = NULL;
    FuncExpr* fexpr = NULL;
    int i;

    /*
    *构建要在transfn FuncExpr节点中使用的参数列表。
    *我们只关心transfn可以在运行时使用get_fn_expr_argtype（）发现实际的参数类型，所以可以使用与任何实际Param都不对应的Param节点。
    */
    argp = makeParam(PARAM_EXEC, -1, agg_state_type, -1, agg_input_collation, -1);
    args = list_make1(argp);

    for (i = agg_num_direct_inputs; i < agg_num_inputs; i++) {
        argp = makeParam(PARAM_EXEC, -1, agg_input_types[i], -1, agg_input_collation, -1);
        args = lappend(args, argp);
    }

    fexpr = makeFuncExpr(transfn_oid, agg_state_type, args, InvalidOid, agg_input_collation, COERCE_EXPLICIT_CALL);
    fexpr->funcvariadic = agg_variadic;
    *transfnexpr = (Expr*)fexpr;

    /*如果没有最后一个函数，将*finalfnexpr设置为NULL*/
    if (!OidIsValid(finalfn_oid)) {
        *finalfnexpr = NULL;
        return;
    }

    /*为最终函数构建表达式树*/
    argp = makeParam(PARAM_EXEC, -1, agg_state_type, -1, agg_input_collation, -1);
    args = list_make1(argp);

    if (agg_ordered_set) {
        for (i = 0; i < agg_num_inputs; i++) {
            argp = makeParam(PARAM_EXEC, -1, agg_input_types[i], -1, agg_input_collation, -1);
            args = lappend(args, argp);
        }
    }

    *finalfnexpr =
        (Expr*)makeFuncExpr(finalfn_oid, agg_result_type, args, InvalidOid, agg_input_collation, COERCE_EXPLICIT_CALL);
    /*finalfn目前从未被视为变量*/
}

/*
 *将groupingSets子句展开为分组集的展平链表。
 *返回的链表按长度（从短到长）排序。
 * 
 *这主要是为planner准备的，但在这里也使用它来做一些一致性检查。
 */
List* expand_grouping_sets(List* groupingSets, int limit)
{
    List* expanded_groups = NIL;
    List* result = NIL;
    double numsets = 1;
    ListCell* lc = NULL;

    if (groupingSets == NIL) {
        return NIL;
    }

    foreach (lc, groupingSets) {
        List* current_result = NIL;
        GroupingSet* gs = (GroupingSet*)lfirst(lc);
        current_result = expand_groupingset_node(gs);
        /*此处para不应为NULL*/
        AssertEreport(current_result != NIL, MOD_OPT, "para should not be NULL here");
        numsets *= list_length(current_result);

        if (limit >= 0 && numsets > limit) {
            return NIL;
        }

        expanded_groups = lappend(expanded_groups, current_result);
    }

    /*
     *在expanded_groups的子列表之间进行笛卡尔积。
     *同时，从单个分组集中删除任何重复的元素（但我们不能更改集合的数量）
     */
    foreach (lc, (List*)linitial(expanded_groups)) {
        result = lappend(result, list_union_int(NIL, (List*)lfirst(lc)));
    }

    for_each_cell(lc, lnext(list_head(expanded_groups)))
    {
        List* p = (List*)lfirst(lc);
        List* new_result = NIL;
        ListCell* lc2 = NULL;

        foreach (lc2, result) {
            List* q = (List*)lfirst(lc2);
            ListCell* lc3 = NULL;

            foreach (lc3, p) {
                new_result = lappend(new_result, list_union_int(q, (List*)lfirst(lc3)));
            }
        }
        result = new_result;
    }

    if (list_length(result) > 1) {
        int result_len = list_length(result);
        List** buf = (List**)palloc(sizeof(List*) * result_len);
        List** ptr = buf;

        foreach (lc, result) {
            *ptr++ = (List*)lfirst(lc);
        }

        qsort(buf, result_len, sizeof(List*), cmp_list_len_asc);

        result = NIL;
        ptr = buf;

        while (result_len-- > 0)
            result = lappend(result, *ptr++);

        pfree_ext(buf);
    }

    return result;
}

/*
 *transformGroupingFunc转换GROUPING表达式
 * 
 *GROUPING（）的行为非常类似于聚合。
 *levels和nesting的处理与aggregates相同。我们也为这些表达式设置了p_hasAggs。
 */
Node* transformGroupingFunc(ParseState* pstate, GroupingFunc* p)
{
    ListCell* lc = NULL;
    List* args = p->args;
    List* result_list = NIL;
    bool orig_is_replace = false;

    GroupingFunc* result = makeNode(GroupingFunc);

    if (list_length(args) > 31) {
        ereport(ERROR,
            (errcode(ERRCODE_TOO_MANY_ARGUMENTS),
                /*GROUPING的参数必须少于32个*/
                errmsg("GROUPING must have fewer than 32 arguments"),
                parser_errposition(pstate, p->location)));
    }
    orig_is_replace = pstate->isAliasReplace;

    /*分组不支持Alias Replace。*/
    pstate->isAliasReplace = false;

    foreach (lc, args) {
        Node* current_result = NULL;
        current_result = transformExpr(pstate, (Node*)lfirst(lc));
        /*稍后检查表达式的可接受性*/
        result_list = lappend(result_list, current_result);
    }

    pstate->isAliasReplace = orig_is_replace;

    result->args = result_list;
    result->location = p->location;

    pstate->p_hasAggs = true;

    return (Node*)result;
}

/*
 *check_windowagg_can_shuffle检查windowagg是否可以打乱次序
 */
bool check_windowagg_can_shuffle(List* partitionClause, List* targetList)
{
    if (partitionClause == NIL) {
        return true;
    }

    ListCell* l = NULL;
    foreach (l, partitionClause) {
        SortGroupClause* grpcl = (SortGroupClause*)lfirst(l);
        TargetEntry* expr = get_sortgroupclause_tle(grpcl, targetList, false);
        if (expr == NULL) {
            continue;
        }
        if (checkExprHasAggs((Node*)expr->expr)) {
            return false;
        }
    }

    return true;
}

/*
 *获取聚合参数类型
 *获取传递给聚合调用的实际数据类型，并返回实际参数的数量。
 *
 *给定一个Aggref，提取输入参数的实际数据类型。
 *对于有序集agg，Aggref包含直接参数和聚合参数，并且直接参数保存在聚合参数之前。
 * 
 *数据类型加载到inputTypes[]中，它必须引用长度为FUNC_MAX_ARGS的数组。
 */
int get_aggregate_argtypes(Aggref* aggref, Oid* inputTypes, int func_max_args)
{
    int narg = 0;
    ListCell* lc = NULL;

    /*
     *如果是有序的set agg，aggref->aggdirectargs不为空。
     *因此，我们需要首先处理直接参数。
     */
    foreach (lc, aggref->aggdirectargs) {
        inputTypes[narg] = exprType((Node*)lfirst(lc));
        narg++;
        if (narg >= func_max_args) {
            ereport(ERROR,
                (errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
                    /*函数最多可以有%d个参数*/
                    errmsg("functions can have at most %d parameters", func_max_args)));
        }
    }

    /*
     *然后获取由普通agg和有序集agg包含的聚合参数。
     */
    foreach (lc, aggref->args) {
        TargetEntry* tle = (TargetEntry*)lfirst(lc);

        /*忽略普通聚合的排序列*/
        if (tle->resjunk) {
            continue;
        }

        inputTypes[narg] = exprType((Node*)tle->expr);
        narg++;
        if (narg >= func_max_args) {
            ereport(ERROR,
                (errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
                    /*函数最多可以有%d个参数*/
                    errmsg("functions can have at most %d parameters", func_max_args)));
        }
    }

    /*narg的值不大于func_max_args*/
    return narg;
}

/*
 *resolve_aggregate_transtype解决聚集转换类型
 *当agg接受ANY或多态类型时，标识聚合调用的转换状态值的数据类型。
 *
 *此函数用于解析多态聚合的状态数据类型。
 *aggtranstype通过搜索pg_aggregate目录以及get_aggregate_argtypes提取的实际参数类型来传递。
 */
Oid resolve_aggregate_transtype(Oid aggfuncid, Oid aggtranstype, Oid* inputTypes, int numArguments)
{
    /*仅在转换状态为多态时解析实际类型*/
    /* Only resolve actual type of transition state when it is polymorphic */
    if (IsPolymorphicType(aggtranstype)) {
        Oid* declaredArgTypes = NULL;
        int agg_nargs = 0;
        /*获取agg函数的参数和结果类型*/
        /* get the agg's function's argument and result types... */
        (void)get_func_signature(aggfuncid, &declaredArgTypes, &agg_nargs);

        Assert(agg_nargs <= numArguments);

        aggtranstype = enforce_generic_type_consistency(inputTypes, declaredArgTypes, agg_nargs, aggtranstype, false);
        pfree(declaredArgTypes);
    }
    return aggtranstype;
}

/*如果宏定义启动了多节点，该函数生效*/
/*寻找group by 子句的行数*/
#ifndef ENABLE_MULTIPLE_NODES
static void find_rownum_in_groupby_clauses(Rownum *rownumVar, check_ungrouped_columns_context *context)
{
    bool haveRownum = false;
    ListCell *gl = NULL;

    /*如果没有未分组参数并且聚合级别不为0*/
    if (!context->have_non_var_grouping || context->sublevels_up != 0) {
        foreach (gl, context->groupClauses) {
            Node *gnode = (Node *)((TargetEntry *)lfirst(gl))->expr;

            if (IsA(gnode, Rownum)) {
                haveRownum = true;
                break;
            }
        }

        /*如果没有行数信息，则报告错误信息*/
        if (haveRownum == false) {
            ereport(ERROR, (errcode(ERRCODE_GROUPING_ERROR),
                /*ROWNUM必须出现在GROUP BY子句中或在聚合函数中使用*/
                errmsg("ROWNUM must appear in the GROUP BY clause or be used in an aggregate function"),
                parser_errposition(context->pstate, rownumVar->location)));
        }
    }
}
#endif

