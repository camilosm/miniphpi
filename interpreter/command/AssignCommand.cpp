#include "AssignCommand.h"

AssignCommand::AssignCommand(int line, Expr* left, AssignOp op, Expr* right):Command(line), m_left(left), m_op(op), m_right(right){
}
AssignCommand::~AssignCommand(){
}

void AssignCommand::execute(){
	Variable* lhs = (Variable*) m_left;
	// NoAssignOp = 1,
	// StdAssignOp = 2,
	// AddAssignOp = 3,
	// SubAssignOp = 4,
	// ConcatAssignOp = 5,
	// MulAssignOp = 6,
	// DivAssignOp = 7,
	// ModAssignOp = 8

	// switch (m_op){
	// 	case NoAssignOp:
	// 		break;

	// 	default:
	// 		break;
	// }
	((Variable*) m_left)->setExpr(m_right->expr());
}
