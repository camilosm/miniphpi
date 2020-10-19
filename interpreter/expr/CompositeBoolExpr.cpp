#include "CompositeBoolExpr.h"

#include <string>

CompositeBoolExpr::CompositeBoolExpr(int line, BoolExpr* left, BoolOp op, BoolExpr* right):
	BoolExpr(line), m_left(left), m_op(op), m_right(right){
}

CompositeBoolExpr::~CompositeBoolExpr(){
	delete m_left;
	delete m_right;
};

bool CompositeBoolExpr::expr(){
	bool value;

	switch (m_op){
		case And:
			value = (m_left->expr() && m_right->expr());
			break;

		case Or:
			value = (m_left->expr() || m_right->expr());
			break;

		default:
			value = false;
			Interruption::semantical(line());
			break;
	}
	return value;
}
