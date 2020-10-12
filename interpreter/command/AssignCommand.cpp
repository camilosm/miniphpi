#include "AssignCommand.h"

AssignCommand::AssignCommand(int line, Expr* left, AssignOp op, Expr* right):Command(line), m_left(left), m_op(op), m_right(right){
}
AssignCommand::~AssignCommand(){
}

void AssignCommand::execute(){
	// std::cout << "executando assign" << std::endl;

	Variable* lhs = (Variable*) m_left;
	lhs->setExpr((Type*)m_right->expr());
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

	// tratamento pra array NAO FUNCIONA
	// ArrayValue* array = (ArrayValue*) m_right;

	// std::map<std::string,Type*> arrayvalue = array->value();
	// std::map<std::string,Type*>::iterator it = arrayvalue.begin();
	// std::string key;
	// Type* value;
	// Variable* dest;
	// while(it!=arrayvalue.end()){
	// 	key = it->first;
	// 	value = it->second;
	// 	dest = lhs->instance(key);
	// 	dest->setExpr(value);
	// }

}
