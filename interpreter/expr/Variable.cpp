#include "Variable.h"

Variable::Variable(int line, const std::string& name)
	:SetExpr(line), m_name(name){
}

Variable::~Variable(){
}

void Variable::setExpr(Type* value){
	Memory::write(m_name, value);
}


Type* Variable::expr(){
	Type* value = Memory::read(m_name);
	if(!value){
		value = new StringValue("");
		setExpr(value);
	}
	return value;

}
