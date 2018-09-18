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

bool isOpenParenthesis(string op)
{
	if (op == "(" || op == "[" || op == "{")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isCloseParenthesis(string op)
{
	if (op == ")" || op == "]" || op == "}")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isOperator(string op)
{
	if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ExpressionManager::isBalanced(string expression)
{
	stack<char> parenthesis;
	bool balanced = true;
	int index = 0;

	while (balanced && index < expression.size())
	{
		char character = expression[index];

		if (isOpenParenthesis(string(1, character)))
		{
			parenthesis.push(character);
		}
		else if (isCloseParenthesis(string(1, character)))
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

string ExpressionManager::postfixEvaluate(string postfixExpression)
{
	stack<int> opStack;
	istringstream iss(postfixExpression);
	vector<string> tokens(istream_iterator<string>{iss}, istream_iterator<string>());
	iss.clear();
	
	if (!isdigit(tokens.at(0)[0])) //if first two tokens are not digits, return invalid
	{
		return "invalid";
	}

	for (string token : tokens)
	{
		if (isdigit(token[0]))
		{
			int num = stoi(token);
			opStack.push(num);
		}
		else if (isOperator(token))
		{
			int left = opStack.top();
			opStack.pop();
			int right = opStack.top();
			opStack.pop();

			if (token == "+") 
			{ 
				opStack.push(right + left); 
			}
			else if (token == "-") 
			{ 
				opStack.push(right - left); 
			}
			else if (token == "*") 
			{ 
				opStack.push(right * left); 
			}
			else if (token == "/") 
			{ 
				if (left != 0)
				{
					opStack.push(right / left);
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
					opStack.push(right % left);
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
	int result = opStack.top();
	return to_string(result);
}

int getPrecedence(string op)
{
	// 2: high precedence, 1: low precedence, 0: no precedence
	if (op == "*" || op == "/" || op == "%")
	{
		return 2;
	}
	else if (op == "+" || op == "-")
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool process_operator(string &op, stack<string> &opStack, string &postfix)
{
	if (opStack.empty() || isOpenParenthesis(opStack.top()) || isOpenParenthesis(op))
	{
		opStack.push(op);
		return true;
	}
	else if (isCloseParenthesis(op))
	{
		if(op == ")")
		{
			while (opStack.top() != "(")
			{
				string value = opStack.top();
				postfix.append(value + " ");
				opStack.pop();

				if (opStack.empty())
				{
					return false;
				}
			}
		}
		else if (op == "]")
		{
			while (opStack.top() != "[")
			{
				string value = opStack.top();
				postfix.append(value + " ");
				opStack.pop();

				if (opStack.empty())
				{
					return false;
				}
			}
		}
		else if (op == "}")
		{
			while (opStack.top() != "{")
			{
				string value = opStack.top();
				postfix.append(value + " ");
				opStack.pop();

				if (opStack.empty())
				{
					return false;
				}
			}
		}

		opStack.pop();
		return true;
	}
	else
	{
		while(opStack.size() > 0 && getPrecedence(op) <= getPrecedence(opStack.top()))
		{
			string value = opStack.top();
			postfix.append(value + " ");
			opStack.pop(); 
		}
		opStack.push(op);
		return true;
	}
}

string ExpressionManager::infixToPostfix(string infixExpression)
{
	string postfix = "";
	stack<string> opStack;
	istringstream iss(infixExpression);
	vector<string> tokens(istream_iterator<string>{iss}, istream_iterator<string>());
	iss.clear();
	for (string token : tokens)
	{
		if (isdigit(token[0]))
		{
			postfix.append(token + " ");
		}
		else if (isOpenParenthesis(token) || isCloseParenthesis(token) || isOperator(token))
		{
			if (!process_operator(token, opStack, postfix)) //calls process_operator, and if it returns false, return "invalid"
			{
				return "invalid";
			}
		}
		else
		{
			return "invalid";
		}
	}
	
	while (!opStack.empty())
	{
		string value = opStack.top();
		postfix.append(value + " ");
		opStack.pop();
	}

	if (postfixEvaluate(postfix) != "invalid")
	{
		return postfix;
	}
	else
	{
		return "invalid";
	}
}

string ExpressionManager::postfixToInfix(string postfixExpression)
{
	return string();
}