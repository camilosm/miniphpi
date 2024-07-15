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
    return Memory::read(m_name);
}
