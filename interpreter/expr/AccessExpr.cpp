#include "AccessExpr.h"

#include <map>
#include <iostream>
#include <string>

AccessExpr::AccessExpr(int line, Expr* base, Expr* index)
	:SetExpr(line), m_base(base), m_index(index){
}

AccessExpr::~AccessExpr(){
	delete m_base;
	delete m_index;
}

Type* AccessExpr::expr(){
	Type* value;
	if(m_index){
		if((!m_base->writable() || m_base->expr()->type() != Type::ArrayType))
			Interruption::semantical(line());

		ArrayValue* base = (ArrayValue*) m_base->expr();
		std::map<std::string,Type*> map = base->value();
		std::string index;
		if(m_index->expr()->type() == Type::IntegerType)
			index = std::to_string(((IntegerValue*) m_index->expr())->value());
		else if(m_index->expr()->type() == Type::StringType)
			index = ((StringValue*) m_index->expr())->value();

		value = map[index];
		return value;
	}
	else{
		return m_base->expr();
	}
}

void AccessExpr::setExpr(Type* value){
	if(m_index){
		if((!m_base->writable() || m_base->expr()->type() != Type::ArrayType))
			Interruption::semantical(line());

		ArrayValue* base = (ArrayValue*) m_base->expr();
		std::map<std::string,Type*> map = base->value();
		std::string index;
		if(m_index->expr()->type() == Type::IntegerType)
			index = std::to_string(((IntegerValue*) m_index->expr())->value());
		else if(m_index->expr()->type() == Type::StringType)
			index = ((StringValue*) m_index->expr())->value();

		map[index] = value;
		((SetExpr*) m_base)->setExpr(new ArrayValue(map));
	}
	else{
		((SetExpr*) m_base->expr())->setExpr(value);
	}
}
