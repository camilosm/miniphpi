#ifndef LEXICAL_ANALYSIS_H
#define LEXICAL_ANALYSIS_H

#include "Lexeme.h"
#include "SymbolTable.h"

class LexicalAnalysis {
    public:
        LexicalAnalysis(const char* filename);
        ~LexicalAnalysis();

        int line() const;
        Lexeme nextToken();

    private:
        int m_line;
        FILE* m_file;
        SymbolTable m_symbol_table;
};

#endif
