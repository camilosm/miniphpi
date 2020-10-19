#ifndef COMPOSITE_BOOL_EXPR_H
#define COMPOSITE_BOOL_EXPR_H

#include "BoolExpr.h"
#include "../util/Interruption.h"

class CompositeBoolExpr: public BoolExpr{
	public:
		enum BoolOp{
			And = 1,
			Or = 2
		};
		CompositeBoolExpr(int line, BoolExpr* left, BoolOp op, BoolExpr* right);
		virtual ~CompositeBoolExpr();
		virtual bool expr();
	private:
		BoolExpr* m_left;
		BoolOp m_op;
		BoolExpr* m_right;
};

#endif
