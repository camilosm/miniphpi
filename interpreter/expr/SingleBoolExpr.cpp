#include "SingleBoolExpr.h"

#include <string>

SingleBoolExpr::SingleBoolExpr(int line, Expr* left, RelOp op, Expr* right):
	BoolExpr(line), m_left(left), m_op(op), m_right(right){
}

SingleBoolExpr::~SingleBoolExpr(){
	delete m_left;
	delete m_right;
};

bool SingleBoolExpr::expr(){
	if(m_left->expr()->type() == Type::ArrayType || m_right->expr()->type() == Type::ArrayType)
		Interruption::semantical(line());

	std::string left;
	if(m_left->expr()->type() == Type::IntegerType)
		left = std::to_string(((IntegerValue*)m_left->expr())->value());
	else
		left = ((StringValue*)m_left->expr())->value();

	std::string right;
	if(m_right->expr()->type() == Type::IntegerType)
		right = std::to_string(((IntegerValue*)m_right->expr())->value());
	else
		right = ((StringValue*)m_right->expr())->value();

	bool value;

	switch (m_op){
		case Equal:
			value = (left == right);
			break;

		case NotEqual:
			value = (left != right);
			break;

		case LowerThan:
			value = (left < right);
			break;

		case LowerEqual:
			value = ((left < right)||(left == right));
			break;

		case GreaterThan:
			value = (left > right);
			break;

		case GreaterEqual:
			value = ((left > right)||(left == right));
			break;

		default:
			value = false;
			Interruption::semantical(line());
			break;
	}
	return value;
}
