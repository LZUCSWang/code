#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100 //初始分配量
#define LISTINCREMENT 10   //增量
typedef int Status;
typedef int ELemType;

//变量定义

//线性表顺序结构：
typedef struct
{
    int *elem;    //存储空间基址 数据类型为int
    int length;   //当前长度
    int listsize; //分配容量
} SqList;
void Intersection_Sq(SqList La, SqList Lb)
{ //实现线性表La = La ∩ Lb
    int e;
    for (int i = 1; i <= La.length; i++)
    {
        GetElem_Sq(La, i, e); //用e依次获取La中的第i个元素
        if (LocateElem_Sq(Lb, e) == 0)
        {                            //判断Lb中是否有元素与e相同
            ListDelete_Sq(La, i, e); //如果有 则删除La中的元素
            i--;                     //这里的i为第i个元素位序 如果删除一个元素后 那么原来第i个元素会变为第i-1个元素
        }
    }
}
int main(){
    
}