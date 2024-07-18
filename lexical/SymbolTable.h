#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <map>
#include <string>

#include "TokenType.h"

class SymbolTable {
    public:
        SymbolTable();

        bool contains(std::string& token) const;
        TokenType find(std::string& token);

    private:
        std::map<std::string, TokenType> m_symbol_table;
};

#endif
