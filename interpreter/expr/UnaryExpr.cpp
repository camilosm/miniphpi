#include "UnaryExpr.h"
#include <string>

UnaryExpr::UnaryExpr(int line, Expr* expr, UnaryOp op)
	:Expr(line), m_expr(expr), m_op(op){
}

UnaryExpr::~UnaryExpr(){
}

Type* UnaryExpr::expr(){
	Type* expr=nullptr;
	int value=0;
	IntegerValue* iv;
	if(!m_expr->writable() || m_expr->expr()->type() == Type::ArrayType)
		Interruption::semantical(line());
	if(m_expr->expr()->type() == Type::StringType){
		StringValue* sv = (StringValue*) m_expr->expr();
		std::string str = sv->value();
		if(str == "")
			value = 0;
		else if(str.find_first_not_of("0123456789") == std::string::npos)
			value = std::stoi(str);
		else
			Interruption::semantical(line());
	}
	else
		value = ((IntegerValue*) m_expr->expr())->value();

	switch (m_op){
		case PreIncOp:
			value++;
			iv = new IntegerValue(value);
			expr = (Type*) iv;
			((SetExpr*)m_expr)->setExpr(iv);
			break;
		case PosIncOp:
			iv = new IntegerValue(value);
			expr = (Type*) iv;
			value++;
			iv = new IntegerValue(value);
			((SetExpr*)m_expr)->setExpr(iv);
			break;
		case PreDecOp:
			value--;
			iv = new IntegerValue(value);
			expr = (Type*) iv;
			((SetExpr*)m_expr)->setExpr(iv);
			break;
		case PosDecOp:
			iv = new IntegerValue(value);
			expr = (Type*) iv;
			value--;
			iv = new IntegerValue(value);
			((SetExpr*)m_expr)->setExpr(iv);
			break;
		default:
			Interruption::semantical(line());
			break;
	}
	return expr;
}
