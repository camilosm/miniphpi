#include "SymbolTable.h"

SymbolTable::SymbolTable() {
    // SYMBOLS
    m_symbol_table["("] = TKN_OPEN_PAR;
    m_symbol_table[")"] = TKN_CLOSE_PAR;
    m_symbol_table["{"] = TKN_OPEN_CUR;
    m_symbol_table["}"] = TKN_CLOSE_CUR;
    m_symbol_table["=>"] = TKN_ARROW;
    m_symbol_table[","] = TKN_COMMA;
    m_symbol_table[";"] = TKN_SEMICOLON;
    m_symbol_table["["] = TKN_OPEN_BRA;
    m_symbol_table["]"] = TKN_CLOSE_BRA;
    m_symbol_table["$"] = TKN_DOLAR;

    // OPERATORS
    m_symbol_table["="] = TKN_ASSIGN;
    m_symbol_table["+="] = TKN_ASSIGN_ADD;
    m_symbol_table["-="] = TKN_ASSIGN_SUB;
    m_symbol_table[".="] = TKN_ASSIGN_CONCAT;
    m_symbol_table["*="] = TKN_ASSIGN_MUL;
    m_symbol_table["/="] = TKN_ASSIGN_DIV;
    m_symbol_table["%="] = TKN_ASSIGN_MOD;
    m_symbol_table["!"] = TKN_NOT;
    m_symbol_table["=="] = TKN_EQUAL;
    m_symbol_table["!="] = TKN_NOT_EQUAL;
    m_symbol_table["<"] = TKN_LOWER;
    m_symbol_table[">"] = TKN_GREATER;
    m_symbol_table["<="] = TKN_LOWER_EQ;
    m_symbol_table[">="] = TKN_GREATER_EQ;
    m_symbol_table["+"] = TKN_ADD;
    m_symbol_table["-"] = TKN_SUB;
    m_symbol_table["."] = TKN_CONCAT;
    m_symbol_table["*"] = TKN_MUL;
    m_symbol_table["/"] = TKN_DIV;
    m_symbol_table["%"] = TKN_MOD;
    m_symbol_table["++"] = TKN_INC;
    m_symbol_table["--"] = TKN_DEC;

    // KEYWORDS
    m_symbol_table["if"] = TKN_IF;
    m_symbol_table["elseif"] = TKN_ELSEIF;
    m_symbol_table["else"] = TKN_ELSE;
    m_symbol_table["while"] = TKN_WHILE;
    m_symbol_table["foreach"] = TKN_FOREACH;
    m_symbol_table["as"] = TKN_AS;
    m_symbol_table["echo"] = TKN_ECHO;
    m_symbol_table["and"] = TKN_AND;
    m_symbol_table["or"] = TKN_OR;
    m_symbol_table["array"] = TKN_ARRAY;
    m_symbol_table["read"] = TKN_READ;
}

bool SymbolTable::contains(std::string& token) const {
    return m_symbol_table.find(token) != m_symbol_table.end();
}

TokenType SymbolTable::find(std::string& token) {
    return this->contains(token) ? m_symbol_table[token] : TKN_INVALID_TOKEN;
}
