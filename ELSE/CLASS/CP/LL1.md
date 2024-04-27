# 分析CFG G1[S]:    S->AB|A|B   A->aAb|a   B->cBd|d  和CFG G2[S]:      S->AB|A|B   A->aAb|e   B->cBd|e  论证：其中一个文法简单调整后即可用于非递归的预测分析而另一个则不行。

王贤义                                                       320210931221                                                      计算机基地班

### (1)对文法的结构和产生语言的分析；可能需要的文法等价变换；对相应文法符号或文法符号串的FRST/FOLLOW集的求解；以及基于上述工作的进一步分析并得出有效结论。

#### 对于G1[S]:  

```
S->AB|A|B
A->aAb|a
B->cBd|d
```

非终结符：{'A', 'B', 'S'}
终结符：{'d', 'b',  'a', 'c'}

- FIRST集和FOLLOW集：

|      | FIRST集       | FOLLOW集          |
| ---- | ------------- | ----------------- |
| S    | {'c','d','a'} | {'#'}             |
| A    | {'a'}         | {'c','b','d','#'} |
| B    | {'c','d'}     | {'d','#'}         |
| AB   | {'a'}         |                   |
| aAb  | {a}           |                   |
| a    | {a}           |                   |
| cBd  | {c}           |                   |
| d    | {d}           |                   |

**显然a和aAb的FIRST集有交集{a}，故该文法不为LL(1)文法**

- 预测分析表：

|      | a           | b    | c      | d    | #    |
| ---- | ----------- | ---- | ------ | ---- | ---- |
| S    | S->A,S->AB  |      | S->B   | S->B |      |
| A    | A->a,A->aAb |      |        |      |      |
| B    |             |      | B->cBd | B->d |      |

**由表格可知G1[S]文法不是LL1文法**

---

#### 对G1进行简单调整

G1‘[S]:

```
S->AE|B
E->B|ε
A->aC
C->Ab|ε
B->cBd|d
```

非终结符：{'E', 'B', 'S', 'C', 'A'}
终结符：{'c', 'b', 'ε', 'a', 'd'}

- FIRST集和FOLLOW集：

|      | FIRST集         | FOLLOW集             |
| ---- | --------------- | -------------------- |
| E    | {'ε', 'c', 'd'} | {'#'}                |
| B    | {'c', 'd'}      | {'d', '#'}           |
| S    | {'a', 'c', 'd'} | {'#'}                |
| C    | {'a', 'ε'}      | {'d', 'c', 'b', '#'} |
| A    | {'a'}           | {'d', 'c', 'b', '#'} |
| AE   | {'a'}           |                      |
| aC   | {'a'}           |                      |
| Ab   | {'a'}           |                      |
| cBd  | {'c'}           |                      |
| d    | {'d'}           |                      |

经分析FIRST(AE)$\cap$FIRST(B)=$\empty$

​			FIRST(B)$\cap$FOLLOW(E)=$\empty$

​			FIRST(Ab)$\cap$FOLLOW(C)=$\empty$

​			FIRST(cBd)$\cap$FIRST(d)=$\empty$

**故G1'[S]文法为LL(1)文法**

- 预测分析表：

|      | c      | b    | a     | d    | #    |
| ---- | ------ | ---- | ----- | ---- | ---- |
| E    | E->B   |      |       | E->B | E->ε |
| B    | B->cBd |      |       | B->d |      |
| S    | S->B   |      | S->AE | S->B |      |
| C    | C->ε   | C->ε | C->Ab | C->ε | C->ε |
| A    |        |      | A->aC |      |      |

**根据预测分析表也可知G1'[S]文法是LL1文法**

---

#### 对于G2[S]:  

```
S->AB|A|B
A->aAb|e
B->cBd|e
```

非终结符：{'A', 'B', 'S'}
终结符：{'d', 'b', 'e', 'a', 'c'}

- FIRST集和FOLLOW集：

| 非终结符 | FIRST集       | FOLLOW集          |
| -------- | ------------- | ----------------- |
| S        | {'c','e','a'} | {'#'}             |
| A        | {'e','a'}     | {'c','b','e','#'} |
| B        | {'c','e'}     | {'d','#'}         |
| AB       | {'a','e'}     |                   |
| eAb      | {'a'}         |                   |
| cBd      | {'c'}         |                   |
| e        | {'e'}         |                   |

**显然FIRST(AB)=FIRST(A)，故不为LL(1)文法**

- 预测分析表：

|      | d    | b    | e               | a          | c      | #    |
| ---- | ---- | ---- | --------------- | ---------- | ------ | ---- |
| S    |      |      | S->A,S->B,S->AB | S->A,S->AB | S->B   |      |
| A    |      |      | A->e            | S->aAb     |        |      |
| B    |      |      | B->e            |            | B->cBd |      |

**由表格可知G2[S]文法不是LL1文法**

---

#### 对G2[S]进行简单调整

```
S->AE|B
E->B|ε
A->aAb|e
B->cBd|e
```

非终结符：{'A', 'E', 'S', 'B'}
终结符：{'ε', 'c', 'a', 'd', 'b', 'e'}

- FIRST集和FOLLOW集：

| 非终结符 | FIRST集         | FOLLOW集             |
| -------- | --------------- | -------------------- |
| A        | {'a', 'e'}      | {'c', '#', 'e', 'b'} |
| E        | {'ε', 'c', 'e'} | {'#'}                |
| S        | {'a', 'c', 'e'} | {'#'}                |
| B        | {'c', 'e'}      | {'#', 'd'}           |
| AE       | {'a','e'}       |                      |
| ε        | {'ε'}           |                      |
| aAb      | {'a'}           |                      |
| e        | {'e'}           |                      |
| cBd      | {'c'}           |                      |

**显然FIRST(AE)$\cap$FIRST(B)={'e'}，故该文法不是LL(1)文法**

- 预测分析表如下：

|      | c      | a      | d    | b    | e          | #    |
| ---- | ------ | ------ | ---- | ---- | ---------- | ---- |
| A    |        | A->aAb |      |      | A->e       |      |
| E    | E->B   |        |      |      | E->B       | E->ε |
| S    | S->B   | S->AE  |      |      | S->B,S->AE |      |
| B    | B->cBd |        |      |      | B->e       |      |

**根据预测分析表可知该文法不是LL(1)文法**



#### 结论：G1[S]经过简单调整后可用于非递归预测分析

---

### (2)构造LL(1)分析表并用于分析某些特定句子

**G1'[S]**预测分析表如下：

|      | c      | b    | a     | d    | #    |
| ---- | ------ | ---- | ----- | ---- | ---- |
| E    | E->B   |      |       | E->B | E->ε |
| B    | B->cBd |      |       | B->d |      |
| S    | S->B   |      | S->AE | S->B |      |
| C    | C->ε   | C->ε | C->Ab | C->ε | C->ε |
| A    |        |      | A->aC |      |      |

**根据预测分析表也可知G1'[S]文法是LL1文法**

使用**G1'[S]**分析**aabcdd**,匹配过程如下:

| 文法符号栈 | 输入串  | 生成式 |
| ---------- | ------- | ------ |
| #S         | aabcdd# | S->AE  |
| #EA        | aabcdd# | A->aC  |
| #ECa       | aabcdd# |        |
| #EC        | abcdd#  | C->Ab  |
| #EbA       | abcdd#  | A->aC  |
| #EbCa      | abcdd#  |        |
| #EbC       | bcdd#   | C->ε   |
| #Eb        | bcdd#   |        |
| #E         | cdd#    | E->B   |
| #B         | cdd#    | B->cBd |
| #dBc       | cdd#    |        |
| #dB        | dd#     | B->d   |
| #dd        | dd#     |        |
| #d         | d#      |        |
| #          | #       |        |

**由表可见每个过程都是唯一的，验证了(1)中的结论**