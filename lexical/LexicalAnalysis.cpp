#include <cstdio>
#include <cctype>
#include <cassert>

#include "LexicalAnalysis.h"

LexicalAnalysis::LexicalAnalysis(const char* filename) : m_line(1) {
    m_file = fopen(filename, "r");
    if (!m_file)
        throw std::runtime_error("Unable to open file");
}

LexicalAnalysis::~LexicalAnalysis() {
    if (m_file != nullptr)
		fclose(m_file);
}

int LexicalAnalysis::line() const {
    return m_line;
}

struct Lexeme LexicalAnalysis::nextToken() {
    struct Lexeme lex;

    int state = 1;
    while (state != 15 && state != 16) {
        int c = getc(m_file);

        switch (state) {
            case 1:
                if (c == ' ' ||
                    c == '\r' ||
                    c == '\t') {
                    state = 1;
                } else if (c == '\n') {
                    m_line++;
                    state = 1;
                } else if (c == '/') {
                    state = 2;
                } else if (c == '+') {
                    lex.token += (char) c;
                    state = 5;
                } else if (c == '-') {
                    lex.token += (char) c;
                    state = 6;
                } else if (c == '.' ||
                            c == '*' ||
                            c == '%' ||
                            c == '!' ||
                            c == '<' ||
                            c == '>') {
                    lex.token += (char) c;
                    state = 7;
                } else if (c == '=') {
                    lex.token += (char) c;
                    state = 8;
                } else if (c == '(' ||
                            c == ')' ||
                            c == '{' ||
                            c == '}' ||
                            c == ';' ||
                            c == ',' ||
                            c == '[' ||
                            c == ']') {
                    lex.token += (char) c;
                    state = 15;
                } else if (isalpha(c)) {
                    lex.token += (char) c;
                    state = 9;
                } else if (c == '$') {
                    lex.token += (char) c;
                    state = 10;
                } else if (isdigit(c)) {
                    lex.token += (char) c;
                    state = 12;
                } else if (c == '\"') {
                    state = 13;
                } else if (c == -1) {
                    lex.type = TKN_END_OF_FILE;
                    state = 16;
                } else {
                    lex.token += (char) c;
                    lex.type = TKN_INVALID_TOKEN;
                    state = 16;
                }
                break;

            case 2:
				if(c == '*')
					state = 3;
				else{
					lex.token += '/';
					ungetc(c, m_file);
					state = 15;
				}
                break;

            case 3:
				if(c == '*')
					state = 4;
				else if(c == -1){
					lex.type = TKN_END_OF_FILE;
					state = 16;
				}
				else
					state = 3;
                break;

            case 4:
				if(c == '*')
					state = 4;
				else if(c == '/')
					state = 1;
				else if(c == -1){
					lex.type = TKN_END_OF_FILE;
					state = 16;
				}
				else
					state = 3;
                break;

            case 5:
				if(c == '+' || c == '='){
					lex.token += (char) c;
					state = 15;
				}
				else{
					if(c != -1)
						ungetc(c, m_file);
					state = 15;
				}
                break;

            case 6:
                if(c == '-' || c == '='){
					lex.token += (char) c;
					state = 15;
				}
				else{
					if(c != -1)
						ungetc(c, m_file);
					state = 15;
				}
                break;

            case 7:
                if (c == '=') {
                    lex.token += (char) c;
                    state = 15;
                } else {
                    // ungetc
                    if (c != -1)
                        ungetc(c, m_file);

                    state = 15;
                }
                break;

            case 8:
                if (c == '>' ||
                    c == '=') {
                    lex.token += (char) c;
                    state = 15;
                } else {
                    // ungetc
                    if (c != -1)
                        ungetc(c, m_file);

                    state = 15;
                }
                break;

            case 9:
                if (isalpha(c)) {
                    lex.token += (char) c;
                    state = 9;
                } else {
                    // ungetc
                    if (c != -1)
                        ungetc(c, m_file);

                    state = 15;
                }
                break;

            case 10:
                if (c == '_' ||
                    isalpha(c)) {
                    lex.token += (char) c;
                    state = 11;
                } else {
                    // ungetc
                    if (c != -1)
                        ungetc(c, m_file);

                    state = 15;
                }
                break;

            case 11:
                if (c == '_' ||
                    isalpha(c) ||
                    isdigit(c)) {
                    lex.token += (char) c;
                    state = 11;
                } else {
                    // ungetc
                    if (c != -1)
                        ungetc(c, m_file);

                    lex.type = TKN_VAR;
                    state = 16;
                }
                break;

            case 12:
				if(isdigit(c)){
					lex.token+= (char) c;
					state = 12;
				}
				else{
					if(c != -1)
						ungetc(c, m_file);
					lex.type = TKN_NUMBER;
					state = 16;
				}
                break;

            case 13:
                if (c == '\\') {
                    state = 14;
                } else if (c == '\"') {
                    lex.type = TKN_STRING;
                    state = 16;
                } else {
                    if (c == -1) {
                        lex.type = TKN_UNEXPECTED_EOF;
                        state = 16;
                    } else {
                        lex.token += (char) c;
                        state = 13;
                    }
                }
                break;

            case 14:
                if (c == 'b') {
                    lex.token += '\b';
                    state = 13;
                } else if (c == 'f') {
                    lex.token += '\f';
                    state = 13;
                } else if (c == 'n') {
                    lex.token += '\n';
                    state = 13;
                } else if (c == 'r') {
                    lex.token += '\r';
                    state = 13;
                } else if (c == 't') {
                    lex.token += '\t';
                    state = 13;
                } else if (c == '\\') {
                    lex.token += '\\';
                    state = 13;
                } else if (c == '\"') {
                    lex.token += '\"';
                    state = 13;
                } else {
                    if (c == -1) {
                        lex.token += '\\';
                        lex.type = TKN_UNEXPECTED_EOF;
                    } else {
                        lex.token += '\\' + c;
                        lex.type = TKN_INVALID_TOKEN;
                    }

                    state = 16;
                }
                break;

            default:
                assert(false);
        }
    }

    if (state == 15)
        lex.type = m_st.find(lex.token);

    return lex;
}
