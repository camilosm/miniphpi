#include "SymbolTable.h"

SymbolTable::SymbolTable() {
    // SYMBOLS
    m_st["("] = TKN_OPEN_PAR;
    m_st[")"] = TKN_CLOSE_PAR;
    m_st["{"] = TKN_OPEN_CUR;
    m_st["}"] = TKN_CLOSE_CUR;
    m_st["=>"] = TKN_ARROW;
    m_st[","] = TKN_COMMA;
    m_st[";"] = TKN_SEMICOLON;
    m_st["["] = TKN_OPEN_BRA;
    m_st["]"] = TKN_CLOSE_BRA;
    m_st["$"] = TKN_DOLAR;

    // OPERATORS
    m_st["="] = TKN_ASSIGN;
    m_st["+="] = TKN_ASSIGN_ADD;
    m_st["-="] = TKN_ASSIGN_SUB;
    m_st[".="] = TKN_ASSIGN_CONCAT;
    m_st["*="] = TKN_ASSIGN_MUL;
    m_st["/="] = TKN_ASSIGN_DIV;
    m_st["%="] = TKN_ASSIGN_MOD;
    m_st["!"] = TKN_NOT;
    m_st["=="] = TKN_EQUAL;
    m_st["!="] = TKN_NOT_EQUAL;
    m_st["<"] = TKN_LOWER;
    m_st[">"] = TKN_GREATER;
    m_st["<="] = TKN_LOWER_EQ;
    m_st[">="] = TKN_GREATER_EQ;
    m_st["+"] = TKN_ADD;
    m_st["-"] = TKN_SUB;
    m_st["."] = TKN_CONCAT;
    m_st["*"] = TKN_MUL;
    m_st["/"] = TKN_DIV;
    m_st["%"] = TKN_MOD;
    m_st["++"] = TKN_INC;
    m_st["--"] = TKN_DEC;

    // KEYWORDS
    m_st["if"] = TKN_IF;
    m_st["elseif"] = TKN_ELSEIF;
    m_st["else"] = TKN_ELSE;
    m_st["while"] = TKN_WHILE;
    m_st["foreach"] = TKN_FOREACH;
    m_st["as"] = TKN_AS;
    m_st["echo"] = TKN_ECHO;
    m_st["and"] = TKN_AND;
    m_st["or"] = TKN_OR;
    m_st["array"] = TKN_ARRAY;
    m_st["read"] = TKN_READ;
}

SymbolTable::~SymbolTable() {
}

bool SymbolTable::contains(std::string token) {
    return m_st.find(token) != m_st.end();
}

enum TokenType SymbolTable::find(std::string token) {
    return this->contains(token) ? m_st[token] : TKN_INVALID_TOKEN;
}
