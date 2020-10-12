#include "Variable.h"

std::map<std::string, Variable*> Variable::m_variables;
StringValue* value = new StringValue("");

Variable::Variable(const std::string& name):SetExpr(-1), m_name(name), m_value((Type*) value){
}

Variable::~Variable(){}

Variable* Variable::instance(const std::string& name){
	Variable* v = m_variables[name];
	if(!v){
		v = new Variable(name);
		m_variables[name] = v;
	}

	return v;
}

Type* Variable::expr(){
	return m_value;
}
