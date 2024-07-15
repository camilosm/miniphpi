#ifndef UNARY_EXPR_H
#define UNARY_EXPR_H

#include "SetExpr.h"
#include "../value/IntegerValue.h"
#include "../value/StringValue.h"
#include "../util/Interruption.h"

class UnaryExpr: public Expr{
    public:
        enum UnaryOp{
            PreIncOp = 1,
            PreDecOp = 2,
            PosIncOp = 3,
            PosDecOp = 4
        };
        UnaryExpr(int line, Expr* expr, UnaryOp op);
        virtual ~UnaryExpr();
        virtual Type* expr();
    private:
        Expr* m_expr;
        UnaryOp m_op;
};

#endif
