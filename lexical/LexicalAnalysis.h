#ifndef LEXICAL_ANALYSIS_H
#define LEXICAL_ANALYSIS_H

#include "Lexeme.h"
#include "SymbolTable.h"

class LexicalAnalysis {
	public:
		LexicalAnalysis(const char* filename);
		virtual ~LexicalAnalysis();

		int line() const;

		struct Lexeme nextToken();

	private:
		int m_line;
		FILE* m_file;
		SymbolTable m_st;
};

#endif
