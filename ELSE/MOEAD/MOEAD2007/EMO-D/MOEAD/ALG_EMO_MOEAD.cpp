#include "ALG_EMO_MOEAD.h"


CALG_EMO_MOEAD::CALG_EMO_MOEAD(void)
{
	s_PBI_type = 3;
}


CALG_EMO_MOEAD::~CALG_EMO_MOEAD(void)
{

}


void CALG_EMO_MOEAD::Execute(int run_id)
{

    this->InitializeParameter();

	this->InitializePopulation();

	this->InitializeNeighborhood();

	int gen = 1;

	for(;;)
	{
		gen++;

		this->EvolvePopulation();
		
		if(IsTerminated()){
			break;
		}

		if((gen%25)==0)
		{ 
			printf("Instance:  %s  RUN:  %d  GEN = %d\n", strTestInstance, run_id, gen);
			this->SavePopulation(run_id);
		}


	}


	this->SavePopulation(run_id);

	m_PopulationSOP.clear();
	v_IdealPoint.clear();

}



void CALG_EMO_MOEAD::InitializeNeighborhood()
{
	vector<double> v_dist   = vector<double>(s_PopulationSize, 0);
	vector<int>    v_indx   = vector<int>(s_PopulationSize, 0);

	unsigned int i, j, k;
	for(i=0; i<s_PopulationSize; i++)
	{
		for(j=0; j<s_PopulationSize; j++)
		{
			v_dist[j] = UtilityToolBox.DistanceVectorNorm2(m_PopulationSOP[i].v_Weight_Vector,//计算两个点权重之间的距离
                                              				m_PopulationSOP[j].v_Weight_Vector);
			v_indx[j] = j;
		}

		UtilityToolBox.Minfastsort(v_dist, //排序（将前neibourhoodsize个放到前面。
			                       v_indx, 
								   s_PopulationSize, 
								   s_NeighborhoodSize);  


		for(k=0; k<s_NeighborhoodSize; k++)//将前neibor个加入到i的邻居当中。
		{
			m_PopulationSOP[i].v_Neighbor_Index.push_back(v_indx[k]);  // save the indexes into neighborhood
		}
	}
	v_dist.clear();
	v_indx.clear();
}


void CALG_EMO_MOEAD::InitializeParameter()
{
char filename[1024];
    
	sprintf_s(filename,"../../SETTINGS/algorithms/MOEAD.txt", strTestInstance);

	char str_temp[1024];
	std::ifstream readf(filename);

	int  flag = 0, i = 0;
	while(!readf.eof())
	{
		readf>>str_temp;

		if(strcmp(str_temp, strTestInstance)==0)
		{
			readf>>s_PopulationSize;
			readf>>s_NeighborhoodSize;
			flag = 1;
			//printf("%d %d", s_PopulationSize, s_NeighborhoodSize); getchar();
			break;
		}
	}
	readf.close();
}



void CALG_EMO_MOEAD::UpdateReference(vector<double> &obj_vect)
{
	for(unsigned n=0; n<NumberOfObjectives; n++)
	{
		if(obj_vect[n]<v_IdealPoint[n])
		{
			v_IdealPoint[n] = obj_vect[n];
		}
	}
}


void CALG_EMO_MOEAD::InitializePopulation()
{
	unsigned i, j;

	s_Fevals_Count = 0;

	v_IdealPoint = vector<double>(NumberOfObjectives, 1.0e+30);   


	char filename1[1024];
	sprintf_s(filename1,"../../SETTINGS/weightvectors/W%d-P%d.dat", NumberOfObjectives, s_PopulationSize);		
	std::ifstream readf(filename1);

	for(i=0; i<s_PopulationSize; i++)
	{
		CSubProblemBase SP;

		SP.m_BestIndividual.Randomize();		//随机生成一个解
		SP.m_BestIndividual.Evaluate();			//计算随机生成的这个解的值
		s_Fevals_Count++;

		UpdateReference(SP.m_BestIndividual.f_obj);    // update reference point
														//用这个随机生成的初始种群更新一下前沿。
		for(j=0; j<NumberOfObjectives; j++)				//将两个目标对应的权重读入
		{
			readf>>SP.v_Weight_Vector[j];
		}

		//SP.Show_Weight_Vector();  	getchar();

		m_PopulationSOP.push_back(SP);				
	}
	readf.close();

	//this->FindNadirPoint();

	//if(s_PBI_type==3) 	NormalizeWeight();
}




void CALG_EMO_MOEAD::FindNadirPoint()
{

	v_NadirPoint = vector<double>(NumberOfObjectives, -1.0e30);

	for(int j=0; j<NumberOfObjectives; j++)
	{
		//*
		vector<double> weight_tch = vector<double>(NumberOfObjectives, 10e-6);
		weight_tch[j] = 1;

		double asf_min = 1.0e+30;
		int    asf_id  = 0;
		for(int s=0; s<s_PopulationSize; s++)
		{
			double tch_max = -1.0e+30;
			for(int k=0; k<NumberOfObjectives; k++)
			{
				double temp = m_PopulationSOP[s].m_BestIndividual.f_obj[k]/weight_tch[k];
				if(temp>tch_max)
				{
				    tch_max = temp;
				}
			}
			if(tch_max<asf_min)
			{
				asf_min = tch_max;
				asf_id  = s;
			}
		}
		v_NadirPoint[j] = m_PopulationSOP[asf_id].m_BestIndividual.f_obj[j];				
	}


	/*
	for(int s=0; s<s_PopulationSize; s++)
	{
		this->NormalizeIndividual(m_PopulationSOP[s].m_BestIndividual);
	}
	*/
}


void CALG_EMO_MOEAD::NormalizeWeight()
{

	for(int s=0; s<s_PopulationSize; s++)
	{
		for(int j=0; j<NumberOfObjectives; j++)
		{
			m_PopulationSOP[s].v_Weight_Vector2[j] = m_PopulationSOP[s].v_Weight_Vector[j]*(v_NadirPoint[j] - v_IdealPoint[j]);			
		}
		UtilityToolBox.NormalizeVector(m_PopulationSOP[s].v_Weight_Vector2);
	}
}


void CALG_EMO_MOEAD::NormalizeIndividual(CIndividualBase &ind)
{
	//ind.Show(1);
	for(int i=0; i<NumberOfObjectives; i++)
	{
		if(abs(v_NadirPoint[i] - v_IdealPoint[i])<1.0e-6)
			ind.f_normal[i] = (ind.f_obj[i] - v_IdealPoint[i])/1.0e-6;		
		else
		    ind.f_normal[i] = (ind.f_obj[i] - v_IdealPoint[i])/(v_NadirPoint[i] - v_IdealPoint[i] + 1.0e-6);		
		//printf("%f ", ind.f_normal[i]);
	}
	//getchar();
}


void CALG_EMO_MOEAD::UpdateProblem(CIndividualBase &child, 
								   unsigned sp_id)
{

	double f1, f2;

	int    id1 = sp_id, id2;

	vector<double> referencepoint = vector<double>(NumberOfObjectives, 0);

	for(int i=0; i<s_NeighborhoodSize; i++)
	{

		id2 = m_PopulationSOP[id1].v_Neighbor_Index[i];//id2为id1领域中的一点。


		//*
		f1 = UtilityToolBox.ScalarizingFunction(m_PopulationSOP[id2].m_BestIndividual.f_obj,//计算id2这个点与参考点的切比雪夫距离，权重向量用的是id2的
              			                        m_PopulationSOP[id2].v_Weight_Vector,
												v_IdealPoint,
												3);  // 1 - TCH  3 - PBI


		f2 = UtilityToolBox.ScalarizingFunction(child.f_obj,								//计算新解。。。权重向量也是用的id2的
                                    			m_PopulationSOP[id2].v_Weight_Vector,
												v_IdealPoint,
												3);
		/*

		if(s_PBI_type==1)
		{

			f1 = UtilityToolBox.ScalarizingFunction(m_PopulationSOP[id2].m_BestIndividual.f_obj,
				m_PopulationSOP[id2].v_Weight_Vector,
				v_IdealPoint,
				3);  // 1 - TCH  3 - PBI


			f2 = UtilityToolBox.ScalarizingFunction(child.f_obj,
				m_PopulationSOP[id2].v_Weight_Vector,
				v_IdealPoint,
				3);
		}


		if(s_PBI_type==2)
		{
			vector<double> referencepoint = vector<double>(NumberOfObjectives, 0);
			this->NormalizeIndividual(m_PopulationSOP[id2].m_BestIndividual);
			f1 = UtilityToolBox.ScalarizingFunction(m_PopulationSOP[id2].m_BestIndividual.f_normal,
				m_PopulationSOP[id2].v_Weight_Vector,
				referencepoint,
				3);  // 1 - TCH  3 - PBI


			this->NormalizeIndividual(child);
			f2 = UtilityToolBox.ScalarizingFunction(child.f_normal,
				m_PopulationSOP[id2].v_Weight_Vector,
				referencepoint,
				3);
		}

		if(s_PBI_type==3)
		{

			f1 = UtilityToolBox.ScalarizingFunction(m_PopulationSOP[id2].m_BestIndividual.f_obj,
				m_PopulationSOP[id2].v_Weight_Vector2,
				v_IdealPoint,
				3);  // 1 - TCH  3 - PBI


			f2 = UtilityToolBox.ScalarizingFunction(child.f_obj,
				m_PopulationSOP[id2].v_Weight_Vector2,
				v_IdealPoint,
				3);
		}
		//*/

		if(f2<f1)
		{
			m_PopulationSOP[id2].m_BestIndividual = child;			//如果可以利用，就直接是新解了。
		}
	}
}




void CALG_EMO_MOEAD::SelectMatingPool(vector<unsigned> &pool, 
									  unsigned sp_id, 
									  unsigned selected_size)
{
	unsigned  id, p;
	while(pool.size()<selected_size)
	{
		id      = unsigned int(s_NeighborhoodSize*UtilityToolBox.Get_Random_Number());
		p       = m_PopulationSOP[sp_id].v_Neighbor_Index[id];

		bool flag = true;
		for(unsigned i=0; i<pool.size(); i++)
		{
			if(pool[i]==p) // parent is in the list
			{
				flag = false;
				break;
			}
		}

		if(flag){
			pool.push_back(p);
		}
	}
}


void CALG_EMO_MOEAD::EvolvePopulation()
{

	if(IsTerminated()) return;

	std::vector<int> order(std::vector<int>(s_PopulationSize,0));//用于打乱而已
	UtilityToolBox.RandomPermutation(order, 0);


	CIndividualBase child;  //子代（新解)
	int p1, p2;
	vector<unsigned> mating_pool;//交配池，两个或三个父辈，取决于遗传算子

	for(unsigned int s=0; s<s_PopulationSize; s++)
	{
		unsigned int id_c = order[s];

		SelectMatingPool(mating_pool, id_c, 2);//从邻居中挑出两父辈进交配池去产生新解出新解。
		p1 = mating_pool[0]; p2 = mating_pool[1]; mating_pool.clear();

		UtilityToolBox.SimulatedBinaryCrossover(m_PopulationSOP[p1].m_BestIndividual.x_var,
			                                    m_PopulationSOP[p2].m_BestIndividual.x_var,
												child.x_var);	//遗传算子产生新解。

		UtilityToolBox.PolynomialMutation(child.x_var, 1.0/NumberOfVariables);
		
		child.Evaluate();   s_Fevals_Count++;//计算新解的函数值

		//this->NormalizeIndividual(child);

		//child.Show(0); getchar();

		UpdateReference(child.f_obj);//用新解的函数值尝试更新参考点
		
		UpdateProblem(child, id_c);//关键，用领域的信息更新

		if(IsTerminated()) break;
	}

	//this->FindNadirPoint();

	//if(s_PBI_type==3)  this->NormalizeWeight();
}


bool CALG_EMO_MOEAD::IsTerminated()
{
	if(s_Fevals_Count>=NumberOfFuncEvals){
		return true;
	}
	else{
		return false;
	}

}


void CALG_EMO_MOEAD::SaveObjSpace(char saveFilename[1024])
{
	std::fstream fout;
	fout.open(saveFilename,std::ios::out);
	for(unsigned n=0; n<s_PopulationSize; n++)
	{
		for(unsigned int k=0; k<NumberOfObjectives; k++)
		{
			fout<<m_PopulationSOP[n].m_BestIndividual.f_obj[k]<<"  ";
		}
		fout<<"\n";
	}
	fout.close();
}



void CALG_EMO_MOEAD::SaveVarSpace(char saveFilename[1024])
{
	std::fstream fout;
	fout.open(saveFilename,std::ios::out);
	for(unsigned n=0; n<s_PopulationSize; n++)
	{
		for(unsigned k=0; k<NumberOfVariables; k++)
		{
			fout<<m_PopulationSOP[n].m_BestIndividual.x_var[k]<<"  ";
		}
		fout<<"\n";
	}
	fout.close();
}

void CALG_EMO_MOEAD::SavePopulation(int run_id)
{
	char filename[1024];
	sprintf_s(filename,"../../SAVING/MOEAD/POF/POF_%s_RUN%d.dat",strTestInstance, run_id);
	SaveObjSpace(filename);//当前种群输出

	//sprintf_s(filename,"Saving/MOEAD/POS_%s_RUN%d.dat",strTestInstance, run_id);
	//SaveVarSpace(filename);
}




