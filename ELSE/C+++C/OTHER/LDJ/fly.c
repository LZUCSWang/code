#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.1415926
struct complex
{
    double real;
    double image;
};
struct complex complex_add(struct complex c1, struct complex c2);
struct complex complex_sub(struct complex c1, struct complex c2);
struct complex complex_multi(struct complex c1, struct complex c2);
struct complex rotation_factor(int N, int n, int k);
double mold_length(struct complex c);
void fft(int len, struct complex in_x[], struct complex out_y[]);

int main()
{
    int sam[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int jhg[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    struct complex x[16];
    struct complex y[16];

    for (int i = 0; i < 16; i++)
    {
        x[i].real = sam[i];
        x[i].image = jhg[i];
    }
    printf("ʱ������\n");

    for (int i = 0; i < 16; i++)
    {
        printf("(%.2f, %.2fi) \n", x[i].real, x[i].image);
    }

    fft(16, x, y);

    printf("Ƶ������\n");

    for (int i = 0; i < 16; i++)
    {
        printf("(%.2f, %.2fi)\n", y[i].real, y[i].image);
    }
    getchar();
    return 0;
}

struct complex complex_add(struct complex c1, struct complex c2) // �����ӷ�
{
    struct complex p;

    p.real = c1.real + c2.real;
    p.image = c1.image + c2.image;

    return p;
}

struct complex complex_sub(struct complex c1, struct complex c2) // ������
{
    struct complex p;

    p.real = c1.real - c2.real;
    p.image = c1.image - c2.image;

    return p;
}

struct complex complex_multi(struct complex c1, struct complex c2) // �����˷�
{
    struct complex c3;
    c3.real = c1.real * c2.real - c1.image * c2.image;
    c3.image = c2.real * c1.image + c1.real * c2.image;

    return c3;
};

struct complex rotation_factor(int N, int n, int k) // ��ת����
{
    struct complex w;

    w.real = cos(2 * PI * n * k / N);
    w.image = -sin(2 * PI * n * k / N);

    return w;
}

double mold_length(struct complex c) // ����
{
    return sqrt(c.real * c.real + c.image * c.image);
};

int reverse_num(int l, int oringin_num) // ��λ��
{
    int q = 0, m = 0;

    for (int k = l - 1; k >= 0; k--)
    {
        q = oringin_num % 2;
        m += q * (1 << k);
        oringin_num = oringin_num / 2;
    }

    return m;
}

void fft(int len, struct complex in_x[], struct complex out_y[])
{
    /*
        param len ���г��ȣ�Ŀǰֻ����2��ָ��
        param in_x���������
        param out_y���������
    */

    int l, k, r, z, dist, q, j; // l�Ǽ�
    struct complex w, tmp;
    struct complex in_x_mem[len];

    l = log2(len);

    for (k = 0; k < len; k++)
    {
        in_x_mem[k] = in_x[reverse_num(l, k)]; // ��λ��Ų���
    }

    for (r = 0; r < l; r++) // ����ÿһ����������
    {

        dist = 1 << r; // ��ǰ����ÿһ���ļ������

        for (j = 0; j < dist; j++) // ��������ǲ���������飬���ϼ��㣬���¼��㣬j�Ǽ������ʼ���
        {
            for (k = j; k < len; k += (dist << 1)) // ���ý��ͣ��û�ͼ���
            {
                q = k + dist;         // qͬһ���������ڶ������
                z = k << (l - r - 1); // ȷ����ת���ӵ�ָ��

                w = rotation_factor(len, 1, z);
                // ���ڲ��ǲ��м��㣬�����Ȼ���
                tmp = in_x_mem[k];

                in_x_mem[k] = complex_add(in_x_mem[k], complex_multi(w, in_x_mem[q]));
                in_x_mem[q] = complex_sub(tmp, complex_multi(w, in_x_mem[q]));
            }
        }
    }
    memcpy(out_y, in_x_mem, len * sizeof(struct complex));
}
