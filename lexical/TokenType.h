#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include <string>

enum TokenType {
    // SPECIALS
    TKN_UNEXPECTED_EOF = -2,
    TKN_INVALID_TOKEN = -1,
    TKN_END_OF_FILE = 0,

    // SYMBOLS
    TKN_OPEN_PAR,       // (
    TKN_CLOSE_PAR,     // )
    TKN_OPEN_CUR,      // {
    TKN_CLOSE_CUR,     // }
    TKN_ARROW,         // =>
    TKN_COMMA,         // ,
    TKN_SEMICOLON,     // ;
    TKN_OPEN_BRA,      // [
    TKN_CLOSE_BRA,     // ]
    TKN_DOLAR,         // $

    // OPERATORS
    TKN_ASSIGN,        // =
    TKN_ASSIGN_ADD,    // +=
    TKN_ASSIGN_SUB,    // -=
    TKN_ASSIGN_CONCAT, // .=
    TKN_ASSIGN_MUL,    // *=
    TKN_ASSIGN_DIV,    // /=
    TKN_ASSIGN_MOD,    // %=
    TKN_NOT,           // !
    TKN_EQUAL,         // ==
    TKN_NOT_EQUAL,     // !=
    TKN_LOWER,         // <
    TKN_GREATER,       // >
    TKN_LOWER_EQ,      // <=
    TKN_GREATER_EQ,    // >=
    TKN_ADD,           // +
    TKN_SUB,           // -
    TKN_CONCAT,        // .
    TKN_MUL,           // *
    TKN_DIV,           // /
    TKN_MOD,           // %
    TKN_INC,           // ++
    TKN_DEC,           // --

    // KEYWORDS
    TKN_IF,           // if
    TKN_ELSEIF,       // elseif
    TKN_ELSE,         // else
    TKN_WHILE,        // while
    TKN_FOREACH,      // foreach
    TKN_AS,           // as
    TKN_ECHO,         // echo
    TKN_AND,          // and
    TKN_OR,           // or
    TKN_ARRAY,        // array
    TKN_READ,         // read

    // OTHERS
    TKN_NUMBER,       // numeros
    TKN_STRING,       // strings
    TKN_VAR          // variable
};

inline std::string tt2str(enum TokenType type){
	switch(type){
		// SPECIALS
		case TKN_UNEXPECTED_EOF:
			return "UNEXPECTED_EOF";
		case TKN_INVALID_TOKEN:
			return "INVALID_TOKEN";
		case TKN_END_OF_FILE:
			return "END_OF_FILE";

		// SYMBOLS
		case TKN_OPEN_PAR:
			return "OPEN_PAR";
		case TKN_CLOSE_PAR:
			return "CLOSE_PAR";
		case TKN_OPEN_CUR:
			return "OPEN_CUR";
		case TKN_CLOSE_CUR:
			return "CLOSE_CUR";
		case TKN_ARROW:
			return "ARROW";
		case TKN_COMMA:
			return "COMMA";
		case TKN_SEMICOLON:
			return "SEMICOLON";
		case TKN_OPEN_BRA:
			return "OPEN_BRA";
		case TKN_CLOSE_BRA:
			return "CLOSE_BRA";
		case TKN_DOLAR:
			return "DOLAR";

		// OPERATORS
		case TKN_ASSIGN:
			return "ASSIGN";
		case TKN_ASSIGN_ADD:
			return "ASSIGN_ADD";
		case TKN_ASSIGN_SUB:
			return "ASSIGN_SUB";
		case TKN_ASSIGN_CONCAT:
			return "ASSIGN_CONCAT";
		case TKN_ASSIGN_MUL:
			return "ASSIGN_MUL";
		case TKN_ASSIGN_DIV:
			return "ASSIGN_DIV";
		case TKN_ASSIGN_MOD:
			return "ASSIGN_MOD";
		case TKN_NOT:
			return "NOT";
		case TKN_EQUAL:
			return "EQUAL";
		case TKN_NOT_EQUAL:
			return "NOT_EQUAL";
		case TKN_LOWER:
			return "LOWER";
		case TKN_GREATER:
			return "GREATER";
		case TKN_LOWER_EQ:
			return "LOWER_EQ";
		case TKN_GREATER_EQ:
			return "GREATER_EQ";
		case TKN_ADD:
			return "ADD";
		case TKN_SUB:
			return "SUB";
		case TKN_CONCAT:
			return "CONCAT";
		case TKN_MUL:
			return "MUL";
		case TKN_DIV:
			return "DIV";
		case TKN_MOD:
			return "MOD";
		case TKN_INC:
			return "INC";
		case TKN_DEC:
			return "DEC";

		// KEYWORDS
		case TKN_IF:
			return "IF";
		case TKN_ELSEIF:
			return "ELSEIF";
		case TKN_ELSE:
			return "ELSE";
		case TKN_WHILE:
			return "WHILE";
		case TKN_FOREACH:
			return "FOREACH";
		case TKN_AS:
			return "AS";
		case TKN_ECHO:
			return "ECHO";
		case TKN_AND:
			return "AND";
		case TKN_OR:
			return "OR";
		case TKN_ARRAY:
			return "ARRAY";
		case TKN_READ:
			return "READ";

		// OTHERS
		case TKN_NUMBER:
			return "NUMBER";
		case TKN_STRING:
			return "STRING";
		case TKN_VAR:
			return "VAR";

		default:
			throw std::string("invalid token type");
	}
}

#endif
