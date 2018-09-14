#include "ExpressionManager.h"


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
	return string();
}

string ExpressionManager::infixToPostfix(string infixExpression)
{
	return string();
}
