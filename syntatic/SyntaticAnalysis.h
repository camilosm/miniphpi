#ifndef SYNTATIC_ANALYSIS_H
#define SYNTATIC_ANALYSIS_H

#include <map>

#include "../lexical/LexicalAnalysis.h"
#include "../interpreter/expr/ArrayExpr.h"
#include "../interpreter/expr/ConstExpr.h"
#include "../interpreter/expr/ReadExpr.h"
#include "../interpreter/expr/Variable.h"
#include "../interpreter/value/IntegerValue.h"
#include "../interpreter/value/StringValue.h"
#include "../interpreter/command/AssignCommand.h"
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

	void semanticalError(int line);
    void matchToken(enum TokenType type);
    void showError();

    BlocksCommand* procCode();
    Command* procStatement();
    void procIf();
    void procWhile();
    void procForeach();
    EchoCommand* procEcho();
    AssignCommand* procAssign();
    void procBoolExpr();
    void procCmpExpr();
    Expr* procExpr();
    Expr* procTerm();
    Expr* procFactor();
    Expr* procArray();
    Expr* procRead();
    Expr* procValue();
    Expr* procAccess();
    Variable* procVarVar();
    ConstExpr* procNumber();
    ConstExpr* procString();
    Variable* procVar();

};

#endif
