#include "SyntaticAnalysis.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>

SyntaticAnalysis::SyntaticAnalysis(LexicalAnalysis& lex)
    : m_lex(lex), m_current(m_lex.nextToken()) {
}

void SyntaticAnalysis::advance() {
    m_current = m_lex.nextToken();
}

void SyntaticAnalysis::eat(TokenType type) {
    // std::cout << "Expected " << tt2str(type) << ", found " << tt2str(m_current.type) << ": \"" << m_current.token << "\"" << std::endl;

    type == m_current.type ? advance() : showError();
}

void SyntaticAnalysis::showError() {
    std::cout << std::setfill('0') << std::setw(2) << m_lex.line() << ": ";
    switch(m_current.type) {
        case TKN_INVALID_TOKEN:
            std::cout << "Lexema inválido [" << m_current.token << "]" << std::endl;
            break;
        case TKN_UNEXPECTED_EOF:
        case TKN_END_OF_FILE:
            std::cout << "Fim de arquivo inesperado" << std::endl;
            break;
        default:
            std::cout << "Lexema não esperado [" << m_current.token << "]" << std::endl;
            break;
    }

    exit(1);
}

Command* SyntaticAnalysis::start() {
    Command* cmd = procCode();
    eat(TKN_END_OF_FILE);
    return cmd;
}

// <code> ::= { <statement> }
BlocksCommand* SyntaticAnalysis::procCode() {
    int line = m_lex.line();

    BlocksCommand* cmds = new BlocksCommand(line);
    Command *cmd;
    while(m_current.type == TKN_IF || m_current.type == TKN_WHILE || m_current.type == TKN_FOREACH || m_current.type == TKN_ECHO || m_current.type == TKN_INC || m_current.type == TKN_DEC || m_current.type == TKN_DOLAR || m_current.type == TKN_VAR || m_current.type == TKN_OPEN_PAR) {
        cmd = procStatement();
        cmds->addCommand(cmd);
    }
    return cmds;
}

// <statement> ::= <if> | <while> | <foreach> | <echo> | <assign>
Command* SyntaticAnalysis::procStatement() {
    Command* cmd = nullptr;
    switch(m_current.type) {
        case TKN_IF:
            cmd = procIf();
            break;
        case TKN_WHILE:
            cmd = procWhile();
            break;
        case TKN_FOREACH:
            cmd = procForeach();
            break;
        case TKN_ECHO:
            cmd = procEcho();
            break;
        case TKN_INC:
        case TKN_DEC:
        case TKN_DOLAR:
        case TKN_VAR:
        case TKN_OPEN_PAR:
            cmd = procAssign();
            break;
        default:
            showError();
            break;
    }
    return cmd;
}

// <if> ::= if '(' <boolexpr> ')' '{' <code> '}'
//              { elseif '(' <boolexpr> ')' '{' <code> '}' }
//              [ else '{' <code> '}' ]
IfCommand* SyntaticAnalysis::procIf() {
    eat(TKN_IF);
    int line = m_lex.line();
    eat(TKN_OPEN_PAR);
    BoolExpr* cond = procBoolExpr();
    eat(TKN_CLOSE_PAR);
    eat(TKN_OPEN_CUR);
    Command* cmd = procCode();
    eat(TKN_CLOSE_CUR);
    IfCommand* ifcmd = new IfCommand(line, cond, cmd);
    IfCommand* anterior = ifcmd;
    while(m_current.type == TKN_ELSEIF) {
        line = m_lex.line();
        advance();
        eat(TKN_OPEN_PAR);
        cond = procBoolExpr();
        eat(TKN_CLOSE_PAR);
        eat(TKN_OPEN_CUR);
        cmd = procCode();
        eat(TKN_CLOSE_CUR);
        IfCommand* elseif = new IfCommand(line, cond, cmd);
        anterior->addElseCommands(elseif);
        anterior = elseif;
    }
    if(m_current.type == TKN_ELSE) {
        line = m_lex.line();
        advance();
        eat(TKN_OPEN_CUR);
        cmd = procCode();
        eat(TKN_CLOSE_CUR);
        anterior->addElseCommands(cmd);
    }
    return ifcmd;
}

// <while> ::= while '(' <boolexpr> ')' '{' <code> '}'
WhileCommand* SyntaticAnalysis::procWhile() {
    eat(TKN_WHILE);
    int line = m_lex.line();
    eat(TKN_OPEN_PAR);
    BoolExpr* cond = procBoolExpr();
    eat(TKN_CLOSE_PAR);
    eat(TKN_OPEN_CUR);
    Command* cmd = procCode();
    eat(TKN_CLOSE_CUR);

    WhileCommand* whilecmd = new WhileCommand(line, cond, cmd);
    return whilecmd;
}

// <foreach> ::= foreach '(' <expr> as <var> [ '=>' <var> ] ')' '{' <code> '}'
ForeachCommand* SyntaticAnalysis::procForeach() {
    eat(TKN_FOREACH);
    int line = m_lex.line();
    eat(TKN_OPEN_PAR);
    Expr* array = procExpr();
    eat(TKN_AS);
    Variable* key = procVar();
    Variable* value = nullptr;
    if(m_current.type == TKN_ARROW) {
        advance();
        value = procVar();
    }
    eat(TKN_CLOSE_PAR);
    eat(TKN_OPEN_CUR);
    Command* cmds = procCode();
    eat(TKN_CLOSE_CUR);
    ForeachCommand* foreach = new ForeachCommand(line, array, cmds, key, value);
    return foreach;
}

// <echo> ::= echo <expr> ';'
EchoCommand* SyntaticAnalysis::procEcho() {
    eat(TKN_ECHO);
    int line = m_lex.line();
    Expr* expr = procExpr();
    EchoCommand* echo = new EchoCommand(line, expr);
    eat(TKN_SEMICOLON);
    return echo;
}

// <assign> ::= <value> [ ('=' | '+=' | '-=' | '.=' | '*=' | '/=' | '%=') <expr> ] ';'
AssignCommand* SyntaticAnalysis::procAssign() {
    int line = m_lex.line();
    Expr* left = procValue();
    AssignCommand::AssignOp op;
    switch(m_current.type) {
        case TKN_ASSIGN:
            op = AssignCommand::StdAssignOp;
            break;
        case TKN_ASSIGN_ADD:
            op = AssignCommand::AddAssignOp;
            break;
        case TKN_ASSIGN_SUB:
            op = AssignCommand::SubAssignOp;
            break;
        case TKN_ASSIGN_CONCAT:
            op = AssignCommand::ConcatAssignOp;
            break;
        case TKN_ASSIGN_MUL:
            op = AssignCommand::MulAssignOp;
            break;
        case TKN_ASSIGN_DIV:
            op = AssignCommand::DivAssignOp;
            break;
        case TKN_ASSIGN_MOD:
            op = AssignCommand::ModAssignOp;
            break;
        case TKN_SEMICOLON:
            op = AssignCommand::NoAssignOp;
            break;
        default:
            showError();
            break;
    }
    AssignCommand* assign;
    if(op!=AssignCommand::NoAssignOp) {
        advance();
        Expr* right = procExpr();
        assign = new AssignCommand(line, left, op, right);
    }
    else
        assign = new AssignCommand(line, left, op);
    eat(TKN_SEMICOLON);
    return assign;
}

// <boolexpr> ::= [ '!' ] <cmpexpr> [ (and | or) <boolexpr> ]
BoolExpr* SyntaticAnalysis::procBoolExpr() {
    BoolExpr* expr;
    if(m_current.type == TKN_NOT) {
        advance();
        BoolExpr* cmpexpr = procCmpExpr();
        expr = new NotBoolExpr(m_lex.line(), cmpexpr);
    }
    else
        expr = procCmpExpr();
    if(m_current.type == TKN_AND || m_current.type == TKN_OR) {
        CompositeBoolExpr::BoolOp op;
        if(m_current.type == TKN_ADD)
            op = CompositeBoolExpr::And;
        else
            op = CompositeBoolExpr::Or;
        advance();
        BoolExpr* boolexpr = procBoolExpr();
        expr = new CompositeBoolExpr(m_lex.line(), expr, op, boolexpr);
    }
    return expr;
}

// <cmpexpr> ::= <expr> ('==' | '!=' | '<' | '>' | '<=' | '>=') <expr>
BoolExpr* SyntaticAnalysis::procCmpExpr() {
    Expr* left = procExpr();
    SingleBoolExpr::RelOp op;
    switch(m_current.type) {
        case TKN_EQUAL:
            op = SingleBoolExpr::Equal;
            break;
        case TKN_NOT_EQUAL:
            op = SingleBoolExpr::NotEqual;
            break;
        case TKN_LOWER:
            op = SingleBoolExpr::LowerThan;
            break;
        case TKN_GREATER:
            op = SingleBoolExpr::GreaterThan;
            break;
        case TKN_LOWER_EQ:
            op = SingleBoolExpr::LowerEqual;
            break;
        case TKN_GREATER_EQ:
            op = SingleBoolExpr::GreaterEqual;
            break;
        default:
            showError();
            break;
    }
    advance();
    Expr* right = procExpr();
    return new SingleBoolExpr(m_lex.line(), left, op, right);
}

// <expr> ::= <term> { ('+' | '-' | '.') <term> }
Expr* SyntaticAnalysis::procExpr() {
    Expr* expr;
    expr = procTerm();
    while(m_current.type == TKN_ADD || m_current.type == TKN_SUB || m_current.type == TKN_CONCAT) {
        Expr* right;
        BinaryExpr::BinaryOp op;
        switch(m_current.type) {
            case TKN_ADD:
                op = BinaryExpr::AddOp;
                break;
            case TKN_SUB:
                op = BinaryExpr::SubOp;
                break;
            case TKN_CONCAT:
                op = BinaryExpr::ConcatOp;
                break;
            default:
                showError();
                break;
        }
        advance();
        right = procTerm();
        expr = new BinaryExpr(m_lex.line(), expr, op, right);
    }
    return expr;
}

// <term> ::= <factor> { ('*' | '/' | '%') <factor> }
Expr* SyntaticAnalysis::procTerm() {
    Expr* expr;
    expr = procFactor();
    while(m_current.type == TKN_MUL || m_current.type == TKN_DIV || m_current.type == TKN_MOD) {
        Expr* right;
        BinaryExpr::BinaryOp op;
        switch(m_current.type) {
            case TKN_MUL:
                op = BinaryExpr::MulOp;
                break;
            case TKN_DIV:
                op = BinaryExpr::DivOp;
                break;
            case TKN_MOD:
                op = BinaryExpr::ModOp;
                break;
            default:
                showError();
                break;
        }
        advance();
        right = procFactor();
        expr = new BinaryExpr(m_lex.line(), expr, op, right);
    }
    return expr;
}

// <factor> ::= <number> | <string> | <array> | <read> | <value>
Expr* SyntaticAnalysis::procFactor() {
    Expr* expr;
    switch(m_current.type) {
        case TKN_NUMBER:
            expr = procNumber();
            break;
        case TKN_STRING:
            expr = procString();
            break;
        case TKN_ARRAY:
            expr = procArray();
            break;
        case TKN_READ:
            expr = procRead();
            break;
        case TKN_INC:
        case TKN_DEC:
        case TKN_DOLAR:
        case TKN_VAR:
        case TKN_OPEN_PAR:
            expr = procValue();
            break;
        default:
            showError();
            break;
    }

    return expr;
}

// <array> ::= array '(' [ <expr> '=>' <expr> { ',' <expr> '=>' <expr> } ] ')'
Expr* SyntaticAnalysis::procArray() {
    eat(TKN_ARRAY);
    eat(TKN_OPEN_PAR);
    int line = m_lex.line();
    ArrayExpr* array = new ArrayExpr(line);
    if(m_current.type == TKN_NUMBER || m_current.type == TKN_STRING || m_current.type == TKN_ARRAY || m_current.type == TKN_READ || m_current.type == TKN_INC || m_current.type == TKN_DEC || m_current.type == TKN_DOLAR || m_current.type == TKN_VAR || m_current.type == TKN_OPEN_PAR) {
        Expr* key;
        Expr* value;
        key = procExpr();
        eat(TKN_ARROW);
        value = procExpr();
        array->insert(key, value);
        while(m_current.type == TKN_COMMA) {
            advance();
            key = procExpr();
            eat(TKN_ARROW);
            value = procExpr();
            array->insert(key, value);
        }
    }
    eat(TKN_CLOSE_PAR);
    return array;
}

// <read> ::= read <expr>
Expr* SyntaticAnalysis::procRead() {
    eat(TKN_READ);
    int line = m_lex.line();
    Expr* msg = procExpr();
    Expr* expr = new ReadExpr(line, msg);
    return expr;
}

// <value> ::= [ ('++' | '--') ] <access> | <access> [ ('++' | '--') ]
Expr* SyntaticAnalysis::procValue() {
    Expr* expr;
    Expr* access;
    int line = m_lex.line();
    if(m_current.type != TKN_DOLAR && m_current.type != TKN_VAR && m_current.type != TKN_OPEN_PAR) {
        if(m_current.type == TKN_INC) {
            advance();
            access = procAccess();
            expr = new UnaryExpr(line, access, UnaryExpr::PreIncOp);
        }
        else if(m_current.type == TKN_DEC) {
            advance();
            access = procAccess();
            expr = new UnaryExpr(line, access, UnaryExpr::PreDecOp);
        }
        else
            showError();
    }
    else {
        access = procAccess();
        expr = access;
        if(m_current.type == TKN_INC) {
            advance();
            expr = new UnaryExpr(line, access, UnaryExpr::PosIncOp);
        }
        else if(m_current.type == TKN_DEC) {
            advance();
            expr = new UnaryExpr(line, access, UnaryExpr::PosDecOp);
        }
    }
    return expr;
}

// <access> ::= ( <varvar> | '(' <expr> ')' ) [ '[' <expr> ']' ]
Expr* SyntaticAnalysis::procAccess() {
    Expr* expr;
    Expr* base;
    if(m_current.type == TKN_DOLAR || m_current.type == TKN_VAR) {
        base = procVarVar();
    }
    else if(m_current.type == TKN_OPEN_PAR) {
        advance();
        base = procExpr();
        eat(TKN_CLOSE_PAR);
    }
    else
        showError();
    if(m_current.type == TKN_OPEN_BRA) {
        advance();
        Expr* index = procExpr();
        expr = new AccessExpr(m_lex.line(), base, index);
        eat(TKN_CLOSE_BRA);
    }
    else
        expr = base;
        // expr = new AccessExpr(m_lex.line(), base);
    return expr;
};

// <varvar> ::= '$' <varvar> | <var>
Expr* SyntaticAnalysis::procVarVar() {
    if(m_current.type == TKN_DOLAR) {
        int line = m_lex.line();
        std::string varvar;
        while(m_current.type == TKN_DOLAR) {
            varvar += "$";
            advance();
        }
        varvar += m_current.token;
        eat(TKN_VAR);
        StringValue* str = new StringValue(varvar);
        Expr* expr = (Expr*) str;
        Expr* varvarexpr = new VarVarExpr(line, expr);
        return varvarexpr;
    }
    else
        return procVar();
}

ConstExpr* SyntaticAnalysis::procNumber() {
    std::string n_str = m_current.token;
    eat(TKN_NUMBER);
    int line = m_lex.line();
    int n = atoi(n_str.c_str());
    IntegerValue* integer = new IntegerValue(n);
    ConstExpr* ce = new ConstExpr(line, integer);
    return ce;
}

ConstExpr* SyntaticAnalysis::procString() {
    std::string str = m_current.token;
    eat(TKN_STRING);
    int line = m_lex.line();
    StringValue* string = new StringValue(str);
    ConstExpr* ce = new ConstExpr(line, string);
    return ce;
}

Variable* SyntaticAnalysis::procVar() {
    std::string nome = m_current.token;
    eat(TKN_VAR);
    int line = m_lex.line();
    Variable* var = new Variable(line, nome);
    return var;
}
