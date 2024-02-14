#include <stdio.h>
int main()
{
    int n;
    int day, year, month;
    int list[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    scanf("%d %d %d %d", &year, &month, &day, &n);
    for (int i = 0; i < n; i++)
    {
        day++;
        if (day == ((year % 4 == 0 && month == 2) ? 29 : list[month - 1]) + 1)
        {
            month++, day = 1;
            if (month == 13)
            {
                year++, month = 1;
            }
        }
    }
    printf("%d %d %d", year, month, day);
}