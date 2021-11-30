#pragma once

#include <string>
using namespace std; 

class InfixCalc {
public:
	InfixCalc(); 
	bool check_for_parenthesis(string user_input);
	bool check_if_operator(char char_to_check); 
	bool check_if_operand(char char_to_check);  
	string convert_to_postfix(string user_input);
	int evaluate(int operator1, int operator2, char operate); 
	int evaluate_postfix(string postfix); 
	int check_op(char op); 
	int get_weight(char op); 
	int get_precedence(char op1, char op2); 
};
