#include "ExpressionManager.h"
#include <vector>
#include <sstream>
#include <istream>
#include <iterator>

ExpressionManager::ExpressionManager()
{
}


ExpressionManager::~ExpressionManager()
{
}

bool ExpressionManager::isBalanced(string expression)
{
	stack<char> parenthesis;
	bool balanced = true;
	int index = 0;

	while (balanced && index < expression.size())
	{
		char character = expression[index];

		if (character == '(' || character == '[' || character == '{')
		{
			parenthesis.push(character);
		}
		else if (character == ')' || character == ']' || character == '}')
		{
			if (parenthesis.size() == 0)
			{
				balanced = false;
			}

			else if (character == ')' && parenthesis.top() != '(')
			{
				balanced = false;
			}
			else if (character == ']' && parenthesis.top() != '[')
			{
				balanced = false;
			}
			else if (character == '}' && parenthesis.top() != '{')
			{
				balanced = false;
			}

			parenthesis.pop();
		}

		index++;
	}

	if (parenthesis.size() == 0 && balanced)
	{
		return true;
	}
	else
	{
		return false;
	}
}

string ExpressionManager::postfixToInfix(string postfixExpression)
{
	return string();
}

string ExpressionManager::postfixEvaluate(string postfixExpression)
{
	stack<int> operands;
	istringstream iss(postfixExpression);
	vector<string> tokens(istream_iterator<string>{iss}, istream_iterator<string>());
	
	if (isdigit(tokens.at(0)[0])) //if first token is not a number, return invalid
	{
		return "invalid";
	}

	for (string token : tokens)
	{
		if (isdigit(token[0]))
		{
			int num = (int)token[0];
			operands.push(num);
		}
		else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%")
		{
			int right = operands.top();
			operands.pop();
			int left = operands.top();
			operands.pop();

			if (token == "+") 
			{ 
				operands.push(right + left); 
			}
			else if (token == "-") 
			{ 
				operands.push(right - left); 
			}
			else if (token == "*") 
			{ 
				operands.push(right * left); 
			}
			else if (token == "/") 
			{ 
				if (left != 0)
				{
					operands.push(right / left);
				}
				else
				{
					return "invalid";
				}
			}
			else if (token == "%") 
			{ 
				if (left != 0)
				{
					operands.push(right % left);
				}
				else
				{
					return "invalid";
				}
			}
		}
		else 
		{
			return "invalid";
		}
	}

	int result = operands.top();
	return to_string(result);
}

string ExpressionManager::infixToPostfix(string infixExpression)
{
	return string();
}
