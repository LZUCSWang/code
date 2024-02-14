// Include the iostream library to be able to input and output to the console
#include <iostream>
// Use the std namespace to avoid typing std:: before cout, cin, and other standard library functions
using namespace std;

void swit()
{
    int work_time, wage_per_hour, wage;
    int count;
    // If the employee worked more than 60 hours, set the count to 3, otherwise calculate the count as the number of 20-hour blocks the employee worked
    if (work_time > 60)
        count = 3;
    else
        count = work_time / 20;
    // Use a switch statement to calculate the employee's wage based on the count of the wage calculation scenario
    switch (count)
    {
    // If the count is 0 or 1, the employee worked less than 20 or between 20 and 40 hours, respectively
    case 0:
    case 1:
        // Calculate the wage as the product of work time and wage per hour
        wage = work_time * wage_per_hour;
        break;
    // If the count is 2, the employee worked between 40 and 60 hours
    case 2:
        // Calculate the wage as the sum of 40 hours at regular wage plus the remaining hours at 1.5 times the regular wage
        wage = ((work_time - 40) * 1.5 + 40) * wage_per_hour;
        break;
    // If the count is 3, the employee worked more than 60 hours
    case 3:
        // Calculate the wage as the sum of 40 hours at regular wage, 20 hours at 1.5 times the regular wage, and the remaining hours at 3 times the regular wage
        wage = ((work_time - 60) * 3 + 20 * 1.5 + 40) * wage_per_hour;
        break;
    }
}
// Define the main function, which is the entry point of the program
int main()
{
    // Define three double variables to store the employee's work time, wage per hour, and total wage
    double work_time, wage_per_hour, wage; // Ask the user to input the employee's work time and wage per hour, and store the inputs in the respective variables
    while (true)
    {
        cout << "Please input employee's work time and wage_per_hour: " << endl;
        cin >> work_time >> wage_per_hour;
        if (work_time == 0)
            break;
        else if (work_time < 0 || work_time > 24 * 7 || wage_per_hour < 0)
        {
            cout << "Invalid input!" << endl;
            continue;
        }
        // If the employee worked 40 hours or less, calculate their wage as the product of work time and wage per hour
        else if (work_time <= 40)
        {
            wage = work_time * wage_per_hour;
        }
        // If the employee worked more than 40 hours but 60 hours or less, calculate their wage as the sum of 40 hours at regular wage plus the remaining hours at 1.5 times the regular wage
        else if (work_time <= 60)
        {
            wage = 40 * wage_per_hour + (work_time - 40) * wage_per_hour * 1.5;
        }
        // If the employee worked more than 60 hours, calculate their wage as the sum of 40 hours at regular wage, 20 hours at 1.5 times the regular wage, and the remaining hours at 3 times the regular wage
        else
        {
            wage = 40 * wage_per_hour + 20 * wage_per_hour * 1.5 + (work_time - 60) * wage_per_hour * 3;
        }
        cout << "The employee's wage: " << wage << endl;
    }
    return 0;
}