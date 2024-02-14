#include <stdio.h>
int main()
{
    int Jan=31, Feb=28, Mar=31, Apr=30, May=31, Jun=30, Jul=31, Aug=31, Sep=30, Oct=31, Nov=30, Dec=31;
    int days, months, years;
    printf("Enter the dates:(2022 1 1)\n");
    scanf("%d%d%d", &years, &months, &days);
    if (years % 4 == 0 && years % 100 != 0 || years % 400 == 0)
        Feb=29;
    switch (months)
    {
        case 1: days += 0; break;
        case 2: days += Jan ; break;
        case 3: days += Jan + Feb ; break;
        case 4: days += Jan + Feb + Mar; break;
        case 5: days += Jan + Feb + Mar + Apr ; break;
        case 6: days += Jan + Feb + Mar + Apr + May; break;
        case 7: days += Jan + Feb + Mar + Apr + May + Jun ; break;
        case 8: days += Jan + Feb + Mar + Apr + May + Jun + Jul; break;
        case 9: days += Jan + Feb + Mar + Apr + May + Jun + Jul + Aug; break;
        case 10: days += Jan + Feb + Mar + Apr + May + Jun + Jul + Aug + Sep; break;
        case 11: days += Jan + Feb + Mar + Apr + May + Jun + Jul + Aug + Sep + Oct; break;
        case 12: days += Jan + Feb + Mar + Apr + May + Jun + Jul + Aug + Sep + Oct + Nov; break;
    }
    return 0&printf("The days is %d\n", days);
}