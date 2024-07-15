#ifndef VAR_VAR_EXPR_H
#define VAR_VAR_EXPR_H

#include "SetExpr.h"
#include "../util/Memory.h"
#include "../util/Interruption.h"


class VarVarExpr: public SetExpr{
    public:
        VarVarExpr(int line, Expr* varvar);
        virtual ~VarVarExpr();

        virtual Type* expr();
        virtual void setExpr(Type* value);

    private:
        virtual std::string process();
        Expr* m_varvar;

};

#endif
