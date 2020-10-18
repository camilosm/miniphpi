#include "VarVarExpr.h"
#include <iostream>

VarVarExpr::VarVarExpr(int line, Expr* varvar)
	:SetExpr(line), m_varvar(varvar){

}

VarVarExpr::~VarVarExpr(){
}

Type* VarVarExpr::process(){
	int i=-1;
	std::string varvar = ((StringValue*) m_varvar)->value();
	Type* value = nullptr;

	while(varvar[0] == '$'){
		i++;
		varvar.erase(0,1);
	}
	while(i--){
		value = Memory::read("$"+varvar);
		if(!value || (i && value->type() != Type::StringType))
			Interruption::semantical(line());
		varvar = ((StringValue*) value)->value();
	}
	value = Memory::read("$"+varvar);
	return value;
}

Type* VarVarExpr::expr(){
	Type* value = process();
	return value;
}

void VarVarExpr::setExpr(Type* value){
	Type* destination = process();
	if(destination->type() != Type::StringType)
		Interruption::semantical(line());
	std::string name = ((StringValue*) destination)->value();
	Memory::write(name, value);
}
