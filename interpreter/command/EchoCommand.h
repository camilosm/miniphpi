#ifndef ECHO_COMMAND_H
#define ECHO_COMMAND_H

#include "Command.h"
#include "../expr/Expr.h"
#include "../value/IntegerValue.h"
#include "../value/StringValue.h"
#include "../value/ArrayValue.h"

class EchoCommand: public Command{
	public:
		EchoCommand(int line, Expr* expr);
		virtual ~EchoCommand();

		virtual void execute();

	private:
		Expr* m_expr;
};

#endif
