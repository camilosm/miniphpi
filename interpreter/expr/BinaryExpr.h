#ifndef BINARY_EXPR_H
#define BINARY_EXPR_H

#include "Expr.h"
#include "../value/IntegerValue.h"
#include "../value/StringValue.h"
#include "../value/ArrayValue.h"
#include "../util/Interruption.h"

class BinaryExpr: public Expr{
	public:
		enum BinaryOp{
			AddOp = 1,
			SubOp = 2,
			ConcatOp = 3,
			MulOp = 4,
			DivOp = 5,
			ModOp = 6
		};
		BinaryExpr(int line, Expr* left, BinaryOp op, Expr*right);
		virtual ~BinaryExpr();
		virtual Type* expr();
	private:
		Expr* m_left;
		BinaryOp m_op;
		Expr* m_right;
};

#endif
