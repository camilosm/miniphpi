#ifndef SYNTATIC_ANALYSIS_H
#define SYNTATIC_ANALYSIS_H

#include <map>

#include "../lexical/LexicalAnalysis.h"
#include "../interpreter/expr/ConstExpr.h"
#include "../interpreter/expr/ReadExpr.h"
#include "../interpreter/value/IntegerValue.h"
#include "../interpreter/value/StringValue.h"
#include "../interpreter/command/Command.h"
#include "../interpreter/command/EchoCommand.h"
#include "../interpreter/command/BlocksCommand.h"


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

    BlocksCommand* procCode();
    Command* procStatement();
    void procIf();
    void procWhile();
    void procForeach();
    EchoCommand* procEcho();
    void procAssign();
    void procBoolExpr();
    void procCmpExpr();
    Expr* procExpr();
    Expr* procTerm();
    Expr* procFactor();
    void procArray();
    Expr* procRead();
    void procValue();
    void procAccess();
    void procVarVar();
    ConstExpr* procNumber();
    ConstExpr* procString();
    void procVar();

};

#endif
