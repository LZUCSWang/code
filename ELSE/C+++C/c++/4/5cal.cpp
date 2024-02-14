#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double num1, num2;
    char op;

    cout << "Enter first number: ";
    cin >> num1;

    cout << "Enter operator (+, -, *, /, ^, r, s, c): ";
    cin >> op;

    if (op == '^')
    {
        cout << "Enter exponent: ";
        cin >> num2;
        cout << pow(num1, num2);
    }
    else if (op == 'r')
    {
        cout << "Enter root: ";
        cin >> num2;
        cout << pow(num1, 1 / num2);
    }
    else if (op == 's')
    {
        cout << "sin(" << num1 << ") = " << sin(num1);
    }
    else if (op == 'c')
    {
        cout << "cos(" << num1 << ") = " << cos(num1);
    }
    else
    {
        cout << "Enter second number: ";
        cin >> num2;

        switch (op)
        {
        case '+':
            cout << num1 + num2;
            break;
        case '-':
            cout << num1 - num2;
            break;
        case '*':
            cout << num1 * num2;
            break;
        case '/':
            cout << num1 / num2;
            break;
        default:
            cout << "Invalid operator";
        }
    }

    return 0;
}
