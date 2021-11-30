#include <string> 
#include <stack>
#include "InfixCalculator.h"


using namespace std; 

InfixCalc::InfixCalc() {

}

string InfixCalc::convert_to_postfix(string user_input)

{
    stack<char> stack_char;
    string return_string = "";
    bool repeated_operator = false;
    bool repeated_operaend = false;
    int length = user_input.length(); 

    for (int i = 0; i < length; i++) {
        if (user_input[i] == ' ' || user_input[i] == ',') continue;
        else if (check_if_operator(user_input[i]))
        {
            if (repeated_operator) {
                return_string = "";
                while (!stack_char.empty())
                {
                    stack_char.pop();
                }
                break;
            }

            while (!stack_char.empty() && stack_char.top() != '(' && get_precedence(stack_char.top(), user_input[i]))
            {
                return_string += stack_char.top();
                stack_char.pop();
            }
            stack_char.push(user_input[i]);
            repeated_operator = true;
            repeated_operaend = false;
        }
        else if (check_if_operand(user_input[i]))
        {
            if (repeated_operaend) {
                return_string = "";
                while (!stack_char.empty())
                {
                    stack_char.pop();
                }
                break;
            }
            return_string += user_input[i];
            repeated_operator = false;
            repeated_operaend = true;
        }
        else if (user_input[i] == '(')
        {
            stack_char.push(user_input[i]);
            repeated_operator = false;
            repeated_operaend = false;
        }
        else if (user_input[i] == ')')
        {
            while (!stack_char.empty() && stack_char.top() != '(') {
                return_string += stack_char.top();
                stack_char.pop();
            }
            if (stack_char.empty()) {
                return_string = "";
                break;
            }
            else {
                stack_char.pop();
            }
            repeated_operator = false;
            repeated_operaend = false;
        }

    }

    while (!stack_char.empty()) {
        return_string += stack_char.top();
        stack_char.pop();
    }
    return return_string;

}

int InfixCalc::evaluate(int operator1, int operator2, char operate) {
    switch (operate) {
    case '*': return operator2 * operator1;
    case '/': return operator2 / operator1;
    case '+': return operator2 + operator1;
    case '-': return operator2 - operator1;
    default: return 0;
    }

}

int InfixCalc::evaluate_postfix(string postfix) {
    stack<int> stack_int;
    int length = postfix.length();
    int i = 0;
    char temp_char;
    int val;

    while (i < length) {

        temp_char = postfix[i];
        if (isdigit(temp_char)) {
            stack_int.push(temp_char - '0');
        }

        else {
            int operator1 = stack_int.top();
            stack_int.pop();
            int operator2 = stack_int.top();
            stack_int.pop();
            val = evaluate(operator1, operator2, temp_char);
            stack_int.push(val);

        }
        i++;

    }
    return val;

}


bool InfixCalc::check_if_operator(char char_to_check)

{
    if (char_to_check == '+' || char_to_check == '-' || char_to_check == '*' || char_to_check == '/' || char_to_check == '$')
        return true;
    return false;

}

bool InfixCalc::check_if_operand(char char_to_check)

{
    if (char_to_check >= '0' && char_to_check <= '9') return true;
    if (char_to_check >= 'a' && char_to_check <= 'z') return true;
    if (char_to_check >= 'A' && char_to_check <= 'Z') return true;
    return false;
}

int InfixCalc::check_op(char op)

{
    if (op == '$') return true;
    return false;
}

int InfixCalc::get_weight(char op)

{
    int return_int = -1;
    switch (op)
    {

    case '*':
    case '/':
        return_int = 2;
    case '+':
    case '-':
        return_int = 1;
    case '$':
        return_int = 3;
    }

    return return_int;

}

int InfixCalc::get_precedence(char op1, char op2)

{

    int op1_weight = get_weight(op1);

    int op2_weight = get_weight(op2);

    if (op1_weight == op2_weight)

    {

        if (check_op(op1)) return false;

        else return true;

    }

    return op1_weight > op2_weight ? true : false;

}


bool InfixCalc::check_for_parenthesis(string user_input)

{
    int count = 0;

    int length = user_input.length();

    for (int i = 0; i < length; i++)

    {
        if (user_input[i] == '(') count++;
        else if (user_input[i] == ')') count--;
        if (count < 0) return false;

    }

    if (count == 0) return true;

    else return false;

}