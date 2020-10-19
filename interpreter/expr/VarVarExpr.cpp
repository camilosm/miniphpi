#include "VarVarExpr.h"
#include <iostream>

VarVarExpr::VarVarExpr(int line, Expr* varvar)
	:SetExpr(line), m_varvar(varvar){

}

VarVarExpr::~VarVarExpr(){
}

std::string VarVarExpr::process(){
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
		if(varvar == "")
			Interruption::semantical(line());
	}
	// value = Memory::read("$"+varvar);
	return varvar;
}

Type* VarVarExpr::expr(){
	std::string varvar = process();
	Type* value = Memory::read("$"+varvar);
	return value;
}

void VarVarExpr::setExpr(Type* value){
	std::string varvar = process();
	Memory::write("$"+varvar, value);
}
