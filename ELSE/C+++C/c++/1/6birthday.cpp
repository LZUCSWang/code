#include <iostream>

using namespace std;

int days_of_month(int year, int month) // 计算某月的天数
{
    if (month == 2)
    {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 29 : 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return 30;
    }
    else
    {
        return 31;
    }
}
int main()
{
    int year, month, day;

    while (true)
    {
        cout << "please enter year month day: " << endl;
        cin >> year >> month >> day;

        if (year == 0 && month == 0 && day == 0)
        {
            break;
        }

        if (year < 1 || month < 1 || month > 12 || day < 1 || day > days_of_month(year, month))
        {
            cout << "Invalid date" << endl;
            continue;
        }
        int total = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;

        bool is_leap_year = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

        for (int m = 1; m < month; m++)
        {
            if (m == 2)
            {
                total += is_leap_year ? 29 : 28;
            }
            else if (m == 4 || m == 6 || m == 9 || m == 11)
            {
                total += 30;
            }
            else
            {
                total += 31;
            }
        }
        total += day;

        int week_day = total % 7;
        switch (week_day)
        {
        case 0:
            cout << "Sunday" << endl;
            break;
        case 1:
            cout << "Monday" << endl;
            break;
        case 2:
            cout << "Tuesday" << endl;
            break;
        case 3:
            cout << "Wednesday" << endl;
            break;
        case 4:
            cout << "Thursday" << endl;
            break;
        case 5:
            cout << "Friday" << endl;
            break;
        case 6:
            cout << "Saturday" << endl;
            break;
        default:
            cout << "Error" << endl;
            break;
        }
    }

    return 0;
}
