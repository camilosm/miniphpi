#ifndef SYNTATIC_ANALYSIS_H
#define SYNTATIC_ANALYSIS_H

#include "../lexical/LexicalAnalysis.h"
#include "../interpreter/expr/AccessExpr.h"
#include "../interpreter/expr/ArrayExpr.h"
#include "../interpreter/expr/BinaryExpr.h"
#include "../interpreter/expr/CompositeBoolExpr.h"
#include "../interpreter/expr/ConstExpr.h"
#include "../interpreter/expr/NotBoolExpr.h"
#include "../interpreter/expr/ReadExpr.h"
#include "../interpreter/expr/SingleBoolExpr.h"
#include "../interpreter/expr/UnaryExpr.h"
#include "../interpreter/expr/Variable.h"
#include "../interpreter/expr/VarVarExpr.h"
#include "../interpreter/value/IntegerValue.h"
#include "../interpreter/value/StringValue.h"
#include "../interpreter/command/AssignCommand.h"
#include "../interpreter/command/BlocksCommand.h"
#include "../interpreter/command/Command.h"
#include "../interpreter/command/EchoCommand.h"
#include "../interpreter/command/ForeachCommand.h"
#include "../interpreter/command/IfCommand.h"
#include "../interpreter/command/WhileCommand.h"

class SyntaticAnalysis {
    public:
        SyntaticAnalysis(LexicalAnalysis& lex);

        Command* start();

    private:
        LexicalAnalysis& m_lex;
        Lexeme m_current;

        void advance();
        void eat(TokenType type);
        void showError();

        BlocksCommand* procCode();
        Command* procStatement();
        IfCommand* procIf();
        WhileCommand* procWhile();
        ForeachCommand* procForeach();
        EchoCommand* procEcho();
        AssignCommand* procAssign();
        BoolExpr* procBoolExpr();
        BoolExpr* procCmpExpr();
        Expr* procExpr();
        Expr* procTerm();
        Expr* procFactor();
        Expr* procArray();
        Expr* procRead();
        Expr* procValue();
        Expr* procAccess();
        Expr* procVarVar();
        ConstExpr* procNumber();
        ConstExpr* procString();
        Variable* procVar();
};

#endif
