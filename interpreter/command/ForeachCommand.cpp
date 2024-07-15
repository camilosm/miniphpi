#include "ForeachCommand.h"

ForeachCommand::ForeachCommand(int line, Expr* expr, Command* cmds, Variable* key, Variable* value):
    Command(line), m_expr(expr), m_cmds(cmds), m_key(key), m_value(value){
}

ForeachCommand::~ForeachCommand(){
    delete m_expr;
    delete m_cmds;
    delete m_key;
    delete m_value;
}
void ForeachCommand::execute(){
    if(!m_key->writable() || (m_value && !m_value->writable()))
        Interruption::semantical(line());

    if(m_expr->expr()->type() != Type::ArrayType)
        Interruption::semantical(line());

    ArrayValue* av = (ArrayValue*) m_expr->expr();
    std::map<std::string,Type*> map = av->value();
    StringValue* sv;
    for(auto it:map){
        sv = new StringValue(it.first);
        ((SetExpr*) m_key)->setExpr(sv);
        if(m_value){
            ((SetExpr*) m_value)->setExpr(it.second);
        }
        m_cmds->execute();
    }
}
