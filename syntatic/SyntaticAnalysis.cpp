#include <cstdlib>
#include <cstdio>
#include <iostream>


#include "SyntaticAnalysis.h"

SyntaticAnalysis::SyntaticAnalysis(LexicalAnalysis& lex) :
    m_lex(lex), m_current(m_lex.nextToken()) {
}

SyntaticAnalysis::~SyntaticAnalysis() {
}

Command* SyntaticAnalysis::start() {
    Command* cmd = procCode();
	matchToken(TKN_END_OF_FILE);
	return cmd;
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
BlocksCommand* SyntaticAnalysis::procCode() {
	int line = m_lex.line();

	BlocksCommand* cmds = new BlocksCommand(line);
	Command *cmd;
	while(m_current.type == TKN_IF || m_current.type == TKN_WHILE || m_current.type == TKN_FOREACH || m_current.type == TKN_ECHO || m_current.type == TKN_INC || m_current.type == TKN_DEC || m_current.type == TKN_DOLAR || m_current.type == TKN_VAR || m_current.type == TKN_OPEN_PAR){
		cmd = procStatement();
		cmds->addCommand(cmd);
	}
	return cmds;
}

// <statement> ::= <if> | <while> | <foreach> | <echo> | <assign>
Command* SyntaticAnalysis::procStatement() {
	Command* cmd;
	switch(m_current.type){
		case TKN_IF:
			printf("\n\nIF\n\n");
			procIf();
			break;
		case TKN_WHILE:
			printf("\n\nWHILE\n\n");
			procWhile();
			break;
		case TKN_FOREACH:
			printf("\n\nFOREACH\n\n");
			procForeach();
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
EchoCommand* SyntaticAnalysis::procEcho() {
	matchToken(TKN_ECHO);
	int line = m_lex.line();
	Expr* expr = procExpr();
	EchoCommand* echo = new EchoCommand(line, expr);
	matchToken(TKN_SEMICOLON);
	return echo;
}

// <assign> ::= <value> [ ('=' | '+=' | '-=' | '.=' | '*=' | '/=' | '%=') <expr> ] ';'
AssignCommand* SyntaticAnalysis::procAssign() {
	int line = m_lex.line();
	Expr* left = procValue();
	enum AssignCommand::AssignOp op;
	switch(m_current.type){
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
	if(op!=AssignCommand::NoAssignOp){
		m_current = m_lex.nextToken();
		Expr* right = procExpr();
		assign = new AssignCommand(line, left, op, right);
	}
	else
		assign = new AssignCommand(line, left, op);
	matchToken(TKN_SEMICOLON);
	return assign;
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
Expr* SyntaticAnalysis::procExpr() {
	Expr* expr;
	expr = procTerm();
	while(m_current.type == TKN_ADD || m_current.type == TKN_SUB || m_current.type == TKN_CONCAT){
		Expr* right;
		BinaryExpr::BinaryOp op;
		switch(m_current.type){
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
		m_current = m_lex.nextToken();
		right = procTerm();
		expr = new BinaryExpr(m_lex.line(), expr, op, right);
	}
	return expr;
}

// <term> ::= <factor> { ('*' | '/' | '%') <factor> }
Expr* SyntaticAnalysis::procTerm() {
	Expr* expr;
	expr = procFactor();
	while(m_current.type == TKN_MUL || m_current.type == TKN_DIV || m_current.type == TKN_MOD){
		Expr* right;
		BinaryExpr::BinaryOp op;
		switch(m_current.type){
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
		m_current = m_lex.nextToken();
		right = procFactor();
		expr = new BinaryExpr(m_lex.line(), expr, op, right);
	}
	return expr;
}

// <factor> ::= <number> | <string> | <array> | <read> | <value>
Expr* SyntaticAnalysis::procFactor() {
	Expr* expr;
	switch(m_current.type){
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
	matchToken(TKN_ARRAY);
	matchToken(TKN_OPEN_PAR);
	int line = m_lex.line();
	ArrayExpr* array = new ArrayExpr(line);
	if(m_current.type == TKN_NUMBER || m_current.type == TKN_STRING || m_current.type == TKN_ARRAY || m_current.type == TKN_READ || m_current.type == TKN_INC || m_current.type == TKN_DEC || m_current.type == TKN_DOLAR || m_current.type == TKN_VAR || m_current.type == TKN_OPEN_PAR){
		Expr* key;
		Expr* value;
		key = procExpr();
		matchToken(TKN_ARROW);
		value = procExpr();
		array->insert(key, value);
		while(m_current.type == TKN_COMMA){
			m_current = m_lex.nextToken();
			key = procExpr();
			matchToken(TKN_ARROW);
			value = procExpr();
			array->insert(key, value);
		}
	}
	matchToken(TKN_CLOSE_PAR);
	return array;
}

// <read> ::= read <expr>
Expr* SyntaticAnalysis::procRead() {
	matchToken(TKN_READ);
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
	if(m_current.type != TKN_DOLAR && m_current.type != TKN_VAR && m_current.type != TKN_OPEN_PAR){
		if(m_current.type == TKN_INC){
			m_current = m_lex.nextToken();
			access = procAccess();
			expr = new UnaryExpr(line, access, UnaryExpr::PreIncOp);
		}
		else if(m_current.type == TKN_DEC){
			m_current = m_lex.nextToken();
			access = procAccess();
			expr = new UnaryExpr(line, access, UnaryExpr::PreDecOp);
		}
		else
			showError();
	}
	else{
		access = procAccess();
		expr = access;
		if(m_current.type == TKN_INC){
			m_current = m_lex.nextToken();
			expr = new UnaryExpr(line, access, UnaryExpr::PosIncOp);
		}
		else if(m_current.type == TKN_DEC){
			m_current = m_lex.nextToken();
			expr = new UnaryExpr(line, access, UnaryExpr::PosDecOp);
		}
	}
	return expr;
}

// <access> ::= ( <varvar> | '(' <expr> ')' ) [ '[' <expr> ']' ]
Expr* SyntaticAnalysis::procAccess() {
	Expr* expr;
	Expr* base;
	if(m_current.type == TKN_DOLAR || m_current.type == TKN_VAR){
		base = procVarVar();
	}
	else if(m_current.type == TKN_OPEN_PAR){
		m_current = m_lex.nextToken();
		base = procExpr();
		matchToken(TKN_CLOSE_PAR);
	}
	else
		showError();
	if(m_current.type == TKN_OPEN_BRA){
		m_current = m_lex.nextToken();
		Expr* index = procExpr();
		expr = new AccessExpr(m_lex.line(), base, index);
		matchToken(TKN_CLOSE_BRA);
	}
	else
		expr = base;
		// expr = new AccessExpr(m_lex.line(), base);
	return expr;
};

// <varvar> ::= '$' <varvar> | <var>
Expr* SyntaticAnalysis::procVarVar() {
	if(m_current.type == TKN_DOLAR){
		std::string varvar;
		while(m_current.type == TKN_DOLAR){
			varvar += "$";
			m_current = m_lex.nextToken();
		}
		varvar += m_current.token;
		int line = m_lex.line();
		matchToken(TKN_VAR);
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
	matchToken(TKN_NUMBER);
	int line = m_lex.line();
	int n = atoi(n_str.c_str());
	IntegerValue* integer = new IntegerValue(n);
	ConstExpr* ce = new ConstExpr(line, integer);
	return ce;
}

ConstExpr* SyntaticAnalysis::procString() {
	std::string str = m_current.token;
	matchToken(TKN_STRING);
	int line = m_lex.line();
	StringValue* string = new StringValue(str);
	ConstExpr* ce = new ConstExpr(line, string);
	return ce;
}

Variable* SyntaticAnalysis::procVar() {
	std::string nome = m_current.token;
	matchToken(TKN_VAR);
	int line = m_lex.line();
	Variable* var = new Variable(line, nome);
	return var;
}
