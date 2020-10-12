#ifndef SET_EXPR_H
#define SET_EXPR_H

#include "Expr.h"

class SetExpr: public Expr{
	public:
		virtual ~SetExpr(){};

		virtual Type* expr() = 0;
		virtual void setExpr(Type* value) = 0;
	protected:
		SetExpr(int line): Expr(line){};
};

#endif
