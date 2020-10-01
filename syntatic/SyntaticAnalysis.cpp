#include <cstdlib>
#include "SyntaticAnalysis.h"

#include "../interpreter/command/Command.h"

SyntaticAnalysis::SyntaticAnalysis(LexicalAnalysis& lex) :
    m_lex(lex), m_current(m_lex.nextToken()) {
}

SyntaticAnalysis::~SyntaticAnalysis() {
}

Command* SyntaticAnalysis::start() {
    return 0;
}

void SyntaticAnalysis::matchToken(enum TokenType type) {
    // printf("Match token: %d -> %d (\"%s\")\n", m_current.type, type, m_current.token.c_str());
    if (type == m_current.type) {
        m_current = m_lex.nextToken();
    } else {
        showError();
    }
}

void SyntaticAnalysis::showError() {
    printf("%02d: ", m_lex.line());

    switch (m_current.type) {
        case TKN_INVALID_TOKEN:
            printf("Lexema inválido [%s]\n", m_current.token.c_str());
            break;
        case TKN_UNEXPECTED_EOF:
        case TKN_END_OF_FILE:
            printf("Fim de arquivo inesperado\n");
            break;
        default:
            printf("Lexema não esperado [%s]\n", m_current.token.c_str());
            break;
    }

    exit(1);
}

// <code> ::= { <statement> }
void SyntaticAnalysis::procCode() {
}

// <statement> ::= <if> | <while> | <foreach> | <echo> | <assign>
void SyntaticAnalysis::procStatement() {
}

// <if> ::= if '(' <boolexpr> ')' '{' <code> '}'
//              { elseif '(' <boolexpr> ')' '{' <code> '}' }
//              [ else '{' <code> '}' ]
void SyntaticAnalysis::procIf() {
}

// <while> ::= while '(' <boolexpr> ')' '{' <code> '}'
void SyntaticAnalysis::procWhile() {
}

// <foreach> ::= foreach '(' <expr> as <var> [ '=>' <var> ] ')' '{' <code> '}'
void SyntaticAnalysis::procForeach() {
}

// <echo> ::= echo <expr> ';'
void SyntaticAnalysis::procEcho() {
}

// <assign> ::= <value> [ ('=' | '+=' | '-=' | '.=' | '*=' | '/=' | '%=') <expr> ] ';'
void SyntaticAnalysis::procAssign() {
}

// <boolexpr> ::= [ '!' ] <cmpexpr> [ (and | or) <boolexpr> ]
void SyntaticAnalysis::procBoolExpr() {
}

// <cmpexpr> ::= <expr> ('==' | '!=' | '<' | '>' | '<=' | '>=') <expr>
void SyntaticAnalysis::procCmpExpr() {
}

// <expr> ::= <term> { ('+' | '-' | '.') <term> }
void SyntaticAnalysis::procExpr() {
}

// <term> ::= <factor> { ('*' | '/' | '%') <factor> }
void SyntaticAnalysis::procTerm() {
}

// <factor> ::= <number> | <string> | <array> | <read> | <value>
void SyntaticAnalysis::procFactor() {
}

// <array> ::= array '(' [ <expr> '=>' <expr> { ',' <expr> '=>' <expr> } ] ')'
void SyntaticAnalysis::procArray() {
}

// <read> ::= read <string>
void SyntaticAnalysis::procRead() {
}

// <value> ::= [ ('++' | '—-') ] <access> | <access> [ ('++' | '--') ]
void SyntaticAnalysis::procValue() {
}

// <access> ::= ( <varvar> | '(' <expr> ')' ) [ '[' <expr> ']' ]
void SyntaticAnalysis::procAccess() {
}

// <varvar> ::= '$' <varvar> | <var>
void SyntaticAnalysis::procVarVar() {
}

void SyntaticAnalysis::procNumber() {
}

void SyntaticAnalysis::procString() {
}

void SyntaticAnalysis::procVar() {
}
