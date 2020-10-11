#ifndef SET_EXPR_H
#define SET_EXPR_H

#include "Expr.h"

class SetExpr: public Expr{
	public:
		virtual ~SetExpr(){};

		Type* expr();
		void setExpr(Type* value);
	protected:
		SetExpr(int line): Expr(line){};

};

#endif
