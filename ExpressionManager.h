#ifndef EXPRESSIONMANAGER_HPP_
#define EXPRESSIONMANAGER_HPP_

#include "ExpressionManagerInterface.h"

class ExpressionManager : ExpressionManagerInterface
{
public:
	ExpressionManager();
	~ExpressionManager();

	// Inherited via ExpressionManagerInterface
	virtual bool isBalanced(string expression) override;
	virtual string postfixToInfix(string postfixExpression) override;
	virtual string postfixEvaluate(string postfixExpression) override;
	virtual string infixToPostfix(string infixExpression) override;
};

#endif // !EXPRESSIONMANAGER_HPP_