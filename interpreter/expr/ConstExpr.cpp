#include "ConstExpr.h"

ConstExpr::ConstExpr(int line, Type* value):
	Expr(line), m_value(value){
}

ConstExpr::~ConstExpr(){}

Type* ConstExpr::expr(){
	return m_value;
}
