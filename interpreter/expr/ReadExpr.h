#ifndef READ_EXPR_H
#define READ_EXPR_H

#include <iostream>
#include <cctype>
#include <string>

#include "Expr.h"
#include "../command/EchoCommand.h"

class ReadExpr: public Expr{
	public:
		ReadExpr(int line, Expr* msg);
		virtual ~ReadExpr();

		virtual Type* expr();

	private:
		Expr* m_msg;

};

#endif
