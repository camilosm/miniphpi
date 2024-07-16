#ifndef LEXEME_H
#define LEXEME_H

#include <string>

#include "TokenType.h"

struct Lexeme {
    std::string token;
    TokenType type;

    Lexeme() : token(""), type(TKN_END_OF_FILE) {}

    const std::string str() {
        return "(\"" + token + "\", " + tt2str(type) + ")";
    }
};

#endif
