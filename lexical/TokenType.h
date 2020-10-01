#ifndef TOKENTYPE_H
#define TOKENTYPE_H

enum TokenType {
    // SPECIALS
    TKN_UNEXPECTED_EOF = -2,
    TKN_INVALID_TOKEN = -1,
    TKN_END_OF_FILE = 0,

    // SYMBOLS
    TKN_OPEN_PAR,      // (
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
    TKN_VAR,          // variable
};

#endif
