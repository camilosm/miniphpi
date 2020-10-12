#ifndef ACCESS_EXPR_H
#define ACCESS_EXPR_H

#include "SetExpr.h"

class AccessExpr: public SetExpr{
	public:
		AccessExpr(int line, Expr* base, Expr* index = nullptr);
		virtual ~AccessExpr(){};
		virtual Type* expr();
		virtual void setExpr(Type* value);
	private:
		Expr* m_base;
		Expr* m_index;
};

#endif
