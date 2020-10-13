#include "AssignCommand.h"
#include <iostream>

AssignCommand::AssignCommand(int line, Expr* left, AssignOp op, Expr* right)
	:Command(line), m_left(left), m_op(op), m_right(right){
}

AssignCommand::~AssignCommand(){
	delete m_left;
	delete m_right;
}

void AssignCommand::execute(){
	// NoAssignOp = 1,
	// StdAssignOp = 2,
	// AddAssignOp = 3,
	// SubAssignOp = 4,
	// ConcatAssignOp = 5,
	// MulAssignOp = 6,
	// DivAssignOp = 7,
	// ModAssignOp = 8

	if(!m_left->writable()){
		printf("%02d: Operação inválida", line());
		exit(1);
	}
	else{
		// switch (m_op){
		// 	case NoAssignOp:
		// 		break;

		// 	default:
		// 		break;
		// }
		SetExpr* lhs = (SetExpr*) m_left;
		lhs->setExpr(m_right->expr());
	}




}
