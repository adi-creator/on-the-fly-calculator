#include <conio.h>
#include <iostream>
#include <string>

using namespace std;

int evaluateExpression(const string& expression, size_t& index);

// evaluate a number in the expression
int evaluateNumber(const string& expression, size_t& index)
{
    int num = 0;
    while (index < expression.size() && isdigit(expression[index]))
    {
        num = num * 10 + (expression[index] - '0');
        index += 1;
    }
    return num;
}

// evaluate a factor in the expression (number or expression in parentheses)
int evaluateFactor(const string& expression, size_t& index)
{
    if (expression[index] == '(')
    {
        index += 1;
        int result = evaluateExpression(expression, index);
        index += 1;  // Move past ')'
        return result;
    }
    else
    {
        return evaluateNumber(expression, index);
    }
}

// evaluate a term in the expression (*, /, ^ operations)
int evaluateTerm(const string& expression, size_t& index)
{
    int result = evaluateFactor(expression, index);

    while (index < expression.size() && (expression[index] == '*' || expression[index] == '/'))
    {
        char operation = expression[index++];
        int nextOperand = evaluateFactor(expression, index);

        switch (operation)
        {
        case '*':
            result *= nextOperand;
            break;
        case '/':
            result /= nextOperand;
            break;

        default:
            break;
        }
    }

    return result;
}


// evaluate the entire expression (+, - operations)
int evaluateExpression(const string& expression, size_t& index)
{
    int result = evaluateTerm(expression, index);

    while (index < expression.size() && (expression[index] == '+' || expression[index] == '-'))
    {
        char opretion = expression[index++];
        int nextOperand = evaluateTerm(expression, index);

        switch (opretion)
        {
        case '+':
            result += nextOperand;
            break;
        case '-':
            result -= nextOperand;
            break;
        default:
            break;
        }
    }

    return result;
}

// calculate the result of the user's arithmetic expression
void calculate()
{
    string userInput;
    int openParentheses = 0;
    int closeParentheses = 0;
    int enterCount = 0;
    size_t index = 0;
    int result = 0;
    bool hasOperation = false;  // Flag to check if there is an operation
    bool lastCharWasOperation = false;  // Flag to check if the last character was an operation
    bool lastCharWasParentheses = false;

    cout << "Enter an arithmetic expression(press space for clear, press enter for exit): " << endl;

    char currentChar;
    while (true)
    {
        currentChar = _getch();
        cout << currentChar;

        if (currentChar == 13)
        { // Enter key
            enterCount++;
            if (enterCount == 1)
            {
                cout << endl << "Exiting the program." << endl;
                exit(EXIT_SUCCESS);
            }
        }
        else if (currentChar == ' ')
        {
            enterCount = 0;
            userInput.clear();
            cout << endl << "clear" << endl;  // Clear the line
            lastCharWasOperation = false;  // Reset the flag when clearing the line
        }

        if (currentChar == '(')
        {
            if (!lastCharWasOperation && !userInput.empty() && !lastCharWasParentheses)
            {
                userInput += '*';
            }
            openParentheses++;
        }
        else if (currentChar == ')')
        {
            closeParentheses++;
        }
        // to verify that there is no two consecutive operations
        if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/')
        {
            if (lastCharWasOperation)
            {
                cout << endl << "Error: Two consecutive operations. reseting user input" << endl;
                userInput.clear();
            }
            hasOperation = true;
            lastCharWasOperation = true;
        }
        else
        {
            lastCharWasOperation = false;
        }

        if (currentChar == '(' || currentChar == ')')
        {
            lastCharWasParentheses = true;
        }
        else {
            lastCharWasParentheses = false;
        }

        if (currentChar != ' ')
        {
            userInput += currentChar;
        }
        // execute only if open/close parentheses are even becuase if not  the arithmetic expression can't be valid
        // excute only if there is any operation for not excute if there is only numbers without operations

        if (enterCount == 0 && openParentheses == closeParentheses && !lastCharWasOperation && hasOperation)
        {
            index = 0;
            result = evaluateExpression(userInput, index);
            cout << endl << "Input: " << userInput << "\tResult: " << result << endl;
        }
    }
    cout << endl;

    if (openParentheses != closeParentheses)
    {
        cout << "Error: Mismatched parentheses." << endl;
        exit(EXIT_FAILURE);
    }
}

int main() {
    calculate();

    return 0;
}
