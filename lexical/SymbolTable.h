#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "TokenType.h"

#include <map>
#include <string>

class SymbolTable {
    public:
        SymbolTable();
        virtual ~SymbolTable();

        bool contains(std::string token);
        enum TokenType find(std::string token);

    private:
        std::map<std::string, enum TokenType> m_st;
};

#endif
