#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define NAMELEN 20
#define MAXPETS 10
typedef struct leibie
{
    char petkind[NAMELEN];
    struct leibie *next;
} leibie;//��������һ�����������ڸ���name������еĳ���
typedef struct item
{
    char petname[NAMELEN];
    leibie *many_petkinds;//һ�������ڵ�
} Item;//����Ľṹ��Ϣ
typedef struct trnode
{
    Item item;
    struct trnode *left;
    struct trnode *right;
} Trnode;//���Ľṹ����ָ����ָ�����Ϣ���Ǹ��ṹ��
typedef struct tree
{
    Trnode *root;
    int size;
} Tree;//���Ľṹ
typedef struct pair
{
    Trnode *parent;
    Trnode *child;
} Pair;//���Ĺ�ϵ�ṹ
Trnode *shengchengjiedian(const Item *pi);//�����������Ľڵ�
bool xiangzuoyidong(const Item *i1, const Item *i2);//�������Ľڵ�
bool xiangyouyidong(const Item *i1, const Item *i2);//�������Ľڵ�
void jiedianjiarushu(Trnode *xingdejiedian, Trnode *root);//���ڵ��������
Pair xunzhaojiedianweizhi(const Item *pi, const Tree *ptree);//Ѱ��Ҫ����ڵ�ĺ���λ��
bool tianjiajiedian(const Item *pi, Tree *ptree);//�ӽڵ�
int mulu(void);//Ŀ¼
void jiachongwu_a(Tree *pt);//ѡ�datasa���ܺ���
void zhaochongwu_b(const Tree *pt);//ѡ��b���ܺ���
void shuchuchongwu(Item item, const char *str);//�������
void bianlishubingshuchu(const Trnode *root, void (*pfun)(Item item, const char *temp), const char *str);//������
int main(void) //
{
    Tree pets;
    int choice;
    int count, temp;
    count = temp = 0;
    pets.root = NULL;//��ʼ����
    pets.size = 0;
    while ((choice = mulu()) != 'q')//ѡ�����
    {
        getchar();
        switch (choice)
        {
        case 'datas':
        {
            jiachongwu_a(&pets);
            break;
        }
        case 'b':
        {
            zhaochongwu_b(&pets);
            break;
        }
        }
    }
    puts("Bye.");
    return 0;
}
int mulu(void) //
{
    puts("Enter the letter corresponding to your choice:");
    puts("datas) add pet");
    puts("b) search pets by name");
    return getchar();
}
void jiachongwu_a(Tree *pt) //
{
    Item temp;
    temp.many_petkinds = (leibie *)malloc(sizeof(leibie));
    puts("Please enter name of pet:");
    fgets(temp.petname, NAMELEN, stdin);//��ȡ��������
    puts("Please enter pet leibie:");
    fgets(temp.many_petkinds->petkind, NAMELEN, stdin);//��ȡ�����������
    tianjiajiedian(&temp, pt);//���ڵ����ӵ����е��ܺ���
    free(temp.many_petkinds);
}
void zhaochongwu_b(const Tree *pt) //
{
    Item temp;
    puts("Please enter name of pet you wish to find:");
    fgets(temp.petname, NAMELEN, stdin);//����Ҫ��ѯ�ĳ�������
    printf("All kinds of the \"%s\" pets:\n", temp.petname);
    bianlishubingshuchu(pt->root, shuchuchongwu, temp.petname);//���������Ϣ
}
void shuchuchongwu(Item item, const char *str) //
{
    leibie *temp = item.many_petkinds;
    while (temp != NULL)
    {
        if (0 == strcmp(item.petname, str)) //��ӡ������ͬ�Ĳ�ͬ����ĳ���;
            printf("Pet: %s  leibie: %s\n", item.petname, temp->petkind);//�ҵ�������ͬ�����
        temp = temp->next;//����һ��
    }
}
void bianlishubingshuchu(const Trnode *root, void (*pfun)(Item item, const char *temp), const char *str) //�Ӹ��ڵ����������
{
    if (root != NULL)
    {
        bianlishubingshuchu(root->left, pfun, str);//����������
        (*pfun)(root->item, str);//�����Ϣ
        bianlishubingshuchu(root->right, pfun, str);//����������
    }
}
bool tianjiajiedian(const Item *pi, Tree *ptree) //���ڵ���뵽����
{
    Trnode *find;
    Trnode *xingdejiedian;
    if ((find = xunzhaojiedianweizhi(pi, ptree).child) != NULL)//���λ�ڸ��ڵ�λ�ã�����һ�β���ʱ
    {
        leibie *temp;
        leibie *node = (leibie *)malloc(sizeof(leibie));//Ϊ�ڵ�����ڴ�
        for (temp = find->item.many_petkinds; temp != NULL; temp = temp->next)
            if (strcmp(pi->many_petkinds->petkind, temp->petkind) == 0)
                break;
        strcpy(node->petkind, pi->many_petkinds->petkind);//�����������е����������Ƶ��ڵ��petkind��
        node->next = NULL;
        for (temp = find->item.many_petkinds; temp->next != NULL; temp = temp->next)
            continue;
        temp->next = node;
        return true;
    }
    xingdejiedian = shengchengjiedian(pi);//����һ���µĽڵ�
    ptree->size++;
    if (ptree->root == NULL)
        ptree->root = xingdejiedian;//��Ϊ��ʱֱ�ӽ����ڵ㸳ֵΪ�µĽڵ�
    else
        jiedianjiarushu(xingdejiedian, ptree->root);
    return true;
}
void jiedianjiarushu(Trnode *xingdejiedian, Trnode *root) //���ڵ���뵽����
{
    if (xiangzuoyidong(&xingdejiedian->item, &root->item))
    {
        if (root->left == NULL)
            root->left = xingdejiedian;
        else
            jiedianjiarushu(xingdejiedian, root->left);
    }
    else if (xiangyouyidong(&xingdejiedian->item, &root->item))
    {
        if (root->right == NULL)
            root->right = xingdejiedian;
        else
            jiedianjiarushu(xingdejiedian, root->right);
    }
}
bool xiangzuoyidong(const Item *i1, const Item *i2) //
{
    return strcmp(i1->petname, i2->petname) < 0 ? true : false;
}
bool xiangyouyidong(const Item *i1, const Item *i2) //
{
    return strcmp(i1->petname, i2->petname) > 0 ? true : false;
}
Trnode *shengchengjiedian(const Item *pi) //���ɽڵ㣬����Ϣ���뵽һ�����Ľڵ��в�����
{
    leibie *temp = (leibie *)malloc(sizeof(leibie));
    Trnode *xingdejiedian = (Trnode *)malloc(sizeof(Trnode));
    strcpy(xingdejiedian->item.petname, pi->petname);//���Ƴ������ͳ������
    strcpy(temp->petkind, pi->many_petkinds->petkind);
    temp->next = NULL;//����β������Ϊ��
    xingdejiedian->item.many_petkinds = temp;
    xingdejiedian->left = NULL;
    xingdejiedian->right = NULL;
    return xingdejiedian;
}
Pair xunzhaojiedianweizhi(const Item *pi, const Tree *ptree) //Ѱ�ҽڵ�λ��
{
    Pair posision;
    posision.parent = NULL;
    posision.child = ptree->root;//��λ��Ĭ��Ϊ���ڵ�
    if (posision.child == NULL)
        return posision;
    while (posision.child != NULL)//֪���ýڵ�ΪҶ�ӽڵ�
    {
        if (xiangzuoyidong(pi, &(posision.child->item)))//����
        {
            posision.parent = posision.child;
            posision.child = posision.child->left;
        }
        else if (xiangyouyidong(pi, &(posision.child->item)))//����
        {
            posision.parent = posision.child;
            posision.child = posision.child->right;
        }
        else
            break;
    }
    return posision;
}