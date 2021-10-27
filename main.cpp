#include<iostream>
#include"Stack.h"
#include <stack>
#include <limits>
#include <sstream>
#include"Utility.h"
#include"error_code.h"
#include<math.h>
#include <cstring>
#include <string>
using namespace std;


char get_command();
bool do_command(char command, Stack& numbers);
void introduction();
void instructions();

Error_code binary_command(double (*command)(double, double), Stack& numbers);
void print_errors(Error_code err);

double addition(double a, double b);
double substraction(double a, double b);
double division(double a, double b);
double multiplication(double a, double b);
double exchange(double a, double b);

double calculatePoxfix2(char expression[], int size);
double eval(double lhs, double rhs, char op);
double evalPostfix(std::string const& input);
double int_pow(double base, double exp);
/*
Post: The program has executed simple arithmetic
      commands entered by the user.
Uses: The class Stack and the functions
      introduction, instructions, do_command, and get_command.
*/
int main()
{
    Stack stored_numbers;

    char c = '5';
    int a = 0;
    a = a * 10;
    a += (c - '0');
    cout << a << endl;
    introduction();
    instructions();
    while (do_command(get_command(), stored_numbers))
        ;
}

char get_command()
{
    char command;
    bool waiting = true;
    cout << "Select command and press <Enter>:";

    while (waiting)
    {
        cin >> command;
        command = tolower(command);
        if (command == '?' || command == '=' || command == '+' ||
            command == '-' || command == '*' || command == '/' ||
            command == 'q' || command == 'x' || command == 's' ||
            command == 'a' || command == 'r')
            waiting = false;

        else
        {
            instructions();
        }
    }
    return command;
}

/*
Pre:  The first parameter specifies a valid calculator command.
Post: The command specified by the first parameter
      has been applied to the Stack of numbers given by the second parameter.
      A result of true is returned unless command == 'q'.
Uses: The class Stack.
*/
bool do_command(char command, Stack& numbers)
{
    double p, q;
    
    
    switch (command)
    {
    case '?':
        cout << "Enter a real number: " << flush;
        cin >> p;
        if (numbers.push(p) == overflow)
            cout << "Warning: Stack full, lost number" << endl;
        break;

    case '=':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else
            cout << p << endl;
        break;

    case '+':
        print_errors(binary_command(addition, numbers));
        break;

    case '-':
        print_errors(binary_command(substraction, numbers));
        break;

    case '/':
        print_errors(binary_command(division, numbers));
        break;

    case '*':
        print_errors(binary_command(multiplication, numbers));
        break;

    case 'x':
        print_errors(binary_command(exchange, numbers));
        break;
    case 's':
        while (binary_command(addition, numbers) != underflow)
        {
        }
        break;
    case 'a':
    {
        int i = 1;
        double sum = 0;
        // First sum all items in stack, while keeping track of number of items
        while (binary_command(addition, numbers) != underflow)
        {
            i++;
        }
        // Remove sum from stack and replace it with the average
        numbers.top(sum);
        numbers.pop();
        numbers.push(sum / i);
        break;
    }
    case 'q':
        cout << "Calculation finished.\n";
        return false;
    case 'r':
        {
        string expression_test;
        cout << "Enter the whole expression: "; cin.ignore();  getline(cin, expression_test);
        int n = expression_test.length();
        char expression[50];
        strcpy(expression, expression_test.c_str());
        cout << "The result is " << evalPostfix(expression_test) <<endl;
    }
    }
    

    return true;
}

void introduction()
{
    cout << "Welcome to Postfix calculator.\n";
}

void instructions()
{
    cout << "The program can run (for 1.1.1) \n"
        << "Please enter a valid command:\n"     
        << "[?]push to stack   [=]print top\n"
        << "[x] exchanges the last two stack entries (for 1.1.2)\n"
        << "[s] sums all stack entries (for 1.1.3)\n"
        << "[a] calculates average of all stack entries (for 1.1.4)\n"
        << "[r] enter the whole expression (for 1.1.5) \n"
        << "[+] [-] [*] [/]   are arithmetic operations\n"
        << "[Q]uit.\n";
}

double addition(double a, double b)
{
    return a + b;
}

double substraction(double a, double b)
{
    return a - b;
}
double division(double a, double b)
{
    return a / b;
}
double multiplication(double a, double b)
{
    return a * b;
}
double exchange(double a, double b)
{
    return a;
}

/*
Wrapper function for operations that operate top two numbers from the stack [ + - * / ]
Handles checking for stack empty, full and only one entry in stack when two are needed.

Pre:  The second parameter specifies a function pointer to the command to be applied to stack
Post: The command specified by the parameter
      has been applied to the Stack of numbers given by the second parameter.
      A result of success is returned unless stack command fails.
Uses: The class Stack.
*/
Error_code binary_command(double (*command)(double, double), Stack& numbers)
{
    double p, q;

    if (numbers.top(p) == underflow)
    {
        return underflow;
    }
    else
    {
        numbers.pop();
        if (numbers.top(q) == underflow)
        {
            numbers.push(p);
            return underflow;
        }
       
        if (command == division && p == 0)
        {
            numbers.push(p);
            return div_by_zero;
        }

        else if (command == exchange)
        {
            numbers.pop();
            numbers.push(p);
            numbers.push(q);
        }
        else
        {
            numbers.pop();
            if (numbers.push(command(q, p)) == overflow)
            {
                return overflow;
            }
        }
    }
    return success;
}

void print_errors(Error_code err)
{
    switch (err)
    {
    case underflow:
        cout << "Stack has too few entries" << endl;
        break;

    case overflow:
        cout << "Warning: Stack full, lost result" << endl;
        break;

    case div_by_zero:
        cout << "Cannot divide by zero" << endl;
        break;
    case success:
        break;
    }
}



double int_pow(double base, double exp) {		// Calculating Exponant
    double result = 1;
    while (exp) {
        if (exp == 1)
            result *= base;
        exp /= 2;
        base *= base;
    }
    return result;
}

double eval(double lhs, double rhs, char op)
{
    
    switch (op) {
    case '+': return lhs + rhs;
    case '-': return lhs - rhs;
    case '*': return lhs * rhs;
    case '/':
        if (rhs != 0)
            return lhs / rhs;
    case '^': return int_pow(lhs, rhs);
    
        
        
    } 

    


    return std::numeric_limits<double>::quiet_NaN();
}



double evalPostfix(std::string const& input)
{
    std::stack<double> values;
    std::stack<char> ops;
    std::stringstream ss{ input };

    for (;;) {
        for (;;) {
            auto pos{ ss.tellg() };  // remember position to restore if
            double value;
            if (!(ss >> value)) {   // extraction fails.
                ss.clear();
                ss.seekg(pos);
                break;
            }
            values.push(value);
        }

        char op;
        if (!(ss >> std::skipws >> op))
            break;

        if (op != '+' && op != '-' && op != '*' && op != '/') {
            std::cerr << '\'' << op << "' is not a valid operator!\n\n";
            return std::numeric_limits<double>::quiet_NaN();
        }

        if (values.size() < 2) {
            std::cerr << "Not enough values!\n\n";
            return std::numeric_limits<double>::quiet_NaN();
        }

        double op2{ values.top() };
        values.pop();
        double op1{ values.top() };
        values.pop();
        values.push(eval(op1, op2, op));
    }

    if (values.size() > 1) { // if we got here and there is more than 1 value left ...
        std::cerr << "Not enough operators!\n\n";
        return std::numeric_limits<double>::quiet_NaN();
    }

    return values.top();
}