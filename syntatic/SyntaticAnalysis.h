#ifndef SYNTATIC_ANALYSIS_H
#define SYNTATIC_ANALYSIS_H

#include "../lexical/LexicalAnalysis.h"
#include <map>

class Command;

class SyntaticAnalysis {
public:
    explicit SyntaticAnalysis(LexicalAnalysis& lex);
    virtual ~SyntaticAnalysis();

    Command* start();

private:
    LexicalAnalysis& m_lex;
    Lexeme m_current;

    void matchToken(enum TokenType type);
    void showError();

    void procCode();
    void procStatement();
    void procIf();
    void procWhile();
    void procForeach();
    void procEcho();
    void procAssign();
    void procBoolExpr();
    void procCmpExpr();
    void procExpr();
    void procTerm();
    void procFactor();
    void procArray();
    void procRead();
    void procValue();
    void procAccess();
    void procVarVar();
    void procNumber();
    void procString();
    void procVar();

};

#endif
