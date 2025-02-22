#include <iostream>

#include "lexical/LexicalAnalysis.h"
#include "syntatic/SyntaticAnalysis.h"
#include "interpreter/command/Command.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s [MiniPHP File]\n", argv[0]);
        return 1;
    }

    try {
        LexicalAnalysis l(argv[1]);

        // This section runs the interpreter.
        // TODO: uncomment after lexical analysis is ok.
        SyntaticAnalysis s(l);
        Command* c = s.start();
        c->execute();
        delete c;

        // This section is meant to test the lexical analiser.
        // TODO: comment after lexical analysis is ok.
        // Lexeme lex;
        // while ((lex = l.nextToken()).type > 0) {
        //     printf("(\"%s\", %s)\n", lex.token.c_str(), tt2str(lex.type).c_str());
        // }

        // switch (lex.type) {
        //     case TKN_INVALID_TOKEN:
        //         printf("%02d: Lexema inválido [%s]\n", l.line(), lex.token.c_str());
        //         break;
        //     case TKN_UNEXPECTED_EOF:
        //         printf("%02d: Fim de arquivo inesperado\n", l.line());
        //         break;
        //     default:
        //         printf("(\"%s\", %s)\n", lex.token.c_str(), tt2str(lex.type).c_str());
        //         break;
        // }
    } catch (std::string msg) {
        fprintf(stderr, "Internal error: %s\n", msg.c_str());
        return 2;
    }

    return 0;
}
