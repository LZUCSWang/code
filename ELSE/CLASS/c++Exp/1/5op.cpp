#include <iostream>
#include <sstream>
using namespace std;
int main()
{
    // Use a while loop to repeatedly ask the user for an arithmetic expression until they enter "0 0 0"
    while (true)
    {
        // Prompt the user to input an arithmetic expression
        cout << "Please input arithmetic expression: "; // Declare a string variable to store the user's input
        string line;
        // Use getline to read a line of text from the console into the line variable
        getline(cin, line);
        // If the user enters "0 0 0", exit the loop
        if (line == "0 0 0")
            break;
        // Create an istringstream object initialized with the user's input to parse the expression
        istringstream iss(line);
        // Declare integer variables a and b to store the operands and a character variable op to store the operator
        int a, b;
        char op;
        // Use the extraction operator to read the operands and operator from the istringstream object
        iss >> a >> op >> b;
        // Check for division by zero, and if found, output an error message and continue the loop
        if (op == '/' && b == 0)
        {
            cout << "Divided by zero!" << endl;
            continue;
        }
        // Declare an integer variable result to store the result of the arithmetic expression
        int result;
        // Use a switch statement to evaluate the operator and calculate the result
        switch (op)
        {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        default:
            cout << "Invalid operator: " << op << endl;
            continue;
        }
        cout << a << op << b << "=" << result << endl;
    }
    return 0;
}