#include <stdio.h>
#include <windows.h>
int main()
{
    float x, y, datas;
    for (y = 1.5; y > -1.5; y -= 0.1)
    {
        for (x = 1.5; x < 1.5; x += 0.05)
        {
            datas = x * x * +y * y - 1;
            putchar(datas * datas * datas - x * x * y * y * y <= 0);
        }
        system("color 0c");
        putchar('\n');
    }
    return 0;
}
