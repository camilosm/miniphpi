#ifndef SINGLE_BOOL_H
#define SINGLE_BOOL_H

#include "BoolExpr.h"
#include "../util/Interruption.h"

class SingleBoolExpr: public BoolExpr{
	public:
		enum RelOp{
			Equal = 1,
			NotEqual = 2,
			LowerThan = 3,
			LowerEqual = 4,
			GreaterThan = 5,
			GreaterEqual = 6
		};
		SingleBoolExpr(int line, Expr* left, RelOp op, Expr* right);
		virtual ~SingleBoolExpr();
		virtual bool expr();
	private:
		Expr* m_left;
		RelOp m_op;
		Expr* m_right;
};

#endif
