#include <stdio.h>
#define M 10
#define N 10
int main()
{
    // double data[5][4],t=0;
    // for (int i=0;i<5;i++){
    //     t=0;
    //     for (int j=0;j<3;j++){
    //         scanf("%lf",&data[i][j]);
    //         t+=data[i][j];
    //     }
    //     data[i][3]=t/3.0;
    // }
    // //输出矩阵
    // printf("每个学生的平均分:\n");
    // for (int i=0;i<5;i++){
    //     for (int j=0;j<3;j++){
    //         printf("%.0lf\t",data[i][j]);
    //     }
    //     printf("%.1lf\n",data[i][3]);
    // }
    // printf("没门课的平均分:\n");
    // for (int j=0;j<3;j++){
    //     double av=0;
    //     for (int i=0;i<5;i++){
    //         av+=data[i][j];
    //     }
    //     printf("%.1lf\t",av/5.0);
    // }

    int datas[M][N];
    int i, j, m, n, t;
    scanf("%d%d", &m, &n); //确定行列数
    /*********Begin*********/
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
            scanf("%d", &datas[i][j]);
    }
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &t);
            printf("%d ", t + datas[i][j]);
        }
        printf("\n");
    }

    /*********End**********/
    return 0;
}