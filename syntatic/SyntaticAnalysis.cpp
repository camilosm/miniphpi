#include <cstdlib>
#include "SyntaticAnalysis.h"

#include "../interpreter/command/Command.h"

SyntaticAnalysis::SyntaticAnalysis(LexicalAnalysis& lex) :
    m_lex(lex), m_current(m_lex.nextToken()) {
}

SyntaticAnalysis::~SyntaticAnalysis() {
}

Command* SyntaticAnalysis::start() {
    procCode();
	// conferir se é aqui que recolhe o token de eof
	matchToken(TKN_END_OF_FILE);
	return 0;
}

void SyntaticAnalysis::matchToken(enum TokenType type) {
    printf("Match token: %d -> %d (\"%s\")\n", m_current.type, type, m_current.token.c_str());
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
	while(m_current.type == TKN_IF || m_current.type == TKN_WHILE || m_current.type == TKN_FOREACH || m_current.type == TKN_ECHO || m_current.type == TKN_INC || m_current.type == TKN_DEC || m_current.type == TKN_DOLAR || m_current.type == TKN_VAR || m_current.type == TKN_OPEN_PAR)
		procStatement();
}

// <statement> ::= <if> | <while> | <foreach> | <echo> | <assign>
void SyntaticAnalysis::procStatement() {
	switch(m_current.type){
		case TKN_IF:
			procIf();
			break;
		case TKN_WHILE:
			procWhile();
			break;
		case TKN_FOREACH:
			procForeach();
			break;
		case TKN_ECHO:
			procEcho();
			break;
		case TKN_INC:
		case TKN_DEC:
		case TKN_DOLAR:
		case TKN_VAR:
		case TKN_OPEN_PAR:
			procAssign();
			break;
		default:
			showError();
			break;
	}
}

// <if> ::= if '(' <boolexpr> ')' '{' <code> '}'
//              { elseif '(' <boolexpr> ')' '{' <code> '}' }
//              [ else '{' <code> '}' ]
void SyntaticAnalysis::procIf() {
	matchToken(TKN_IF);
	matchToken(TKN_OPEN_PAR);
	procBoolExpr();
	matchToken(TKN_CLOSE_PAR);
	matchToken(TKN_OPEN_CUR);
	procCode();
	matchToken(TKN_CLOSE_CUR);
	while(m_current.type == TKN_ELSEIF){
		m_current = m_lex.nextToken();
		matchToken(TKN_OPEN_PAR);
		procBoolExpr();
		matchToken(TKN_CLOSE_PAR);
		matchToken(TKN_OPEN_CUR);
		procCode();
		matchToken(TKN_CLOSE_CUR);
	}
	if(m_current.type == TKN_ELSE){
		m_current = m_lex.nextToken();
		matchToken(TKN_OPEN_CUR);
		procCode();
		matchToken(TKN_CLOSE_CUR);
	}
}

// <while> ::= while '(' <boolexpr> ')' '{' <code> '}'
void SyntaticAnalysis::procWhile() {
	matchToken(TKN_WHILE);
	matchToken(TKN_OPEN_PAR);
	procBoolExpr();
	matchToken(TKN_CLOSE_PAR);
	matchToken(TKN_OPEN_CUR);
	procCode();
	matchToken(TKN_CLOSE_CUR);
}

// <foreach> ::= foreach '(' <expr> as <var> [ '=>' <var> ] ')' '{' <code> '}'
void SyntaticAnalysis::procForeach() {
	matchToken(TKN_FOREACH);
	matchToken(TKN_OPEN_PAR);
	procExpr();
	matchToken(TKN_AS);
	procVar();
	if(m_current.type == TKN_ARROW){
		m_current = m_lex.nextToken();
		procVar();
	}
	matchToken(TKN_CLOSE_PAR);
	matchToken(TKN_OPEN_CUR);
	procCode();
	matchToken(TKN_CLOSE_CUR);
}

// <echo> ::= echo <expr> ';'
void SyntaticAnalysis::procEcho() {
	matchToken(TKN_ECHO);
	procExpr();
	matchToken(TKN_SEMICOLON);
}

// <assign> ::= <value> [ ('=' | '+=' | '-=' | '.=' | '*=' | '/=' | '%=') <expr> ] ';'
void SyntaticAnalysis::procAssign() {
	procValue();
	switch(m_current.type){
		case TKN_ASSIGN:
		case TKN_ASSIGN_ADD:
		case TKN_ASSIGN_SUB:
		case TKN_ASSIGN_CONCAT:
		case TKN_ASSIGN_MUL:
		case TKN_ASSIGN_DIV:
		case TKN_ASSIGN_MOD:
			m_current = m_lex.nextToken();
			procExpr();
			matchToken(TKN_SEMICOLON);
			break;
		case TKN_SEMICOLON:
			m_current = m_lex.nextToken();
			break;
		default:
			showError();
			break;
	}
}

// <boolexpr> ::= [ '!' ] <cmpexpr> [ (and | or) <boolexpr> ]
void SyntaticAnalysis::procBoolExpr() {
	if(m_current.type == TKN_NOT)
		m_current = m_lex.nextToken();
	procCmpExpr();
	if(m_current.type == TKN_AND || m_current.type == TKN_OR){
		m_current = m_lex.nextToken();
		procBoolExpr();
	}
}

// <cmpexpr> ::= <expr> ('==' | '!=' | '<' | '>' | '<=' | '>=') <expr>
void SyntaticAnalysis::procCmpExpr() {
	procExpr();
	switch(m_current.type){
		case TKN_EQUAL:
		case TKN_NOT_EQUAL:
		case TKN_LOWER:
		case TKN_GREATER:
		case TKN_LOWER_EQ:
		case TKN_GREATER_EQ:
			m_current = m_lex.nextToken();
			break;
		default:
			showError();
			break;
	}
	procExpr();
}

// <expr> ::= <term> { ('+' | '-' | '.') <term> }
void SyntaticAnalysis::procExpr() {
	procTerm();
	while(m_current.type == TKN_ADD || m_current.type == TKN_SUB || m_current.type == TKN_CONCAT){
		m_current = m_lex.nextToken();
		procTerm();
	}
}

// <term> ::= <factor> { ('*' | '/' | '%') <factor> }
void SyntaticAnalysis::procTerm() {
	procFactor();
	while(m_current.type == TKN_MUL || m_current.type == TKN_DIV || m_current.type == TKN_MOD){
		m_current = m_lex.nextToken();
		procFactor();
	}
}

// <factor> ::= <number> | <string> | <array> | <read> | <value>
void SyntaticAnalysis::procFactor() {
	switch(m_current.type){
		case TKN_NUMBER:
			procNumber();
			break;
		case TKN_STRING:
			procString();
			break;
		case TKN_ARRAY:
			procArray();
			break;
		case TKN_READ:
			procRead();
			break;
		case TKN_INC:
		case TKN_DEC:
		case TKN_DOLAR:
		case TKN_VAR:
		case TKN_OPEN_PAR:
			procValue();
			break;
		default:
			showError();
			break;
	}
}

// <array> ::= array '(' [ <expr> '=>' <expr> { ',' <expr> '=>' <expr> } ] ')'
void SyntaticAnalysis::procArray() {
	matchToken(TKN_ARRAY);
	matchToken(TKN_OPEN_PAR);
	if(m_current.type == TKN_NUMBER || m_current.type == TKN_STRING || m_current.type == TKN_ARRAY || m_current.type == TKN_READ || m_current.type == TKN_INC || m_current.type == TKN_DEC || m_current.type == TKN_DOLAR || m_current.type == TKN_VAR || m_current.type == TKN_OPEN_PAR){
		procExpr();
		matchToken(TKN_ARROW);
		procExpr();
		while(m_current.type == TKN_COMMA){
			m_current = m_lex.nextToken();
			procExpr();
			matchToken(TKN_ARROW);
			procExpr();
		}
	}
	matchToken(TKN_CLOSE_PAR);
}

// <read> ::= read <string>
void SyntaticAnalysis::procRead() {
	matchToken(TKN_READ);
	procString();
}

// <value> ::= [ ('++' | '--') ] <access> | <access> [ ('++' | '--') ]
void SyntaticAnalysis::procValue() {
	if(m_current.type != TKN_DOLAR && m_current.type != TKN_VAR && m_current.type != TKN_OPEN_PAR){
		if(m_current.type == TKN_INC || m_current.type == TKN_DEC)
			m_current = m_lex.nextToken();
		else
			showError();
		procAccess();
	}
	else{
		procAccess();
		if(m_current.type == TKN_INC || m_current.type == TKN_DEC)
			m_current = m_lex.nextToken();
	}
}

// <access> ::= ( <varvar> | '(' <expr> ')' ) [ '[' <expr> ']' ]
void SyntaticAnalysis::procAccess() {
	if(m_current.type == TKN_DOLAR || m_current.type == TKN_VAR)
		procVarVar();
	else if(m_current.type == TKN_OPEN_PAR){
		m_current = m_lex.nextToken();
		procExpr();
		matchToken(TKN_CLOSE_PAR);
	}
	else
		showError();
	if(m_current.type == TKN_OPEN_BRA){
		m_current = m_lex.nextToken();
		procExpr();
		matchToken(TKN_CLOSE_BRA);
	}
}

// <varvar> ::= '$' <varvar> | <var>
void SyntaticAnalysis::procVarVar() {
	if(m_current.type == TKN_DOLAR){
		m_current = m_lex.nextToken();
		procVarVar();
	}
	else
		procVar();
}

void SyntaticAnalysis::procNumber() {
	matchToken(TKN_NUMBER);
}

void SyntaticAnalysis::procString() {
	matchToken(TKN_STRING);
}

void SyntaticAnalysis::procVar() {
	matchToken(TKN_VAR);
}
