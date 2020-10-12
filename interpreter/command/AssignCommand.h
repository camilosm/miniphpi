#ifndef ASSIGN_COMMAND_H
#define ASSIGN_COMMAND_H

#include "Command.h"
#include "../expr/Expr.h"
#include "../expr/Variable.h"
#include "../value/ArrayValue.h"

class AssignCommand: public Command{
	public:
		enum AssignOp {
            NoAssignOp = 1,
			StdAssignOp = 2,
			AddAssignOp = 3,
			SubAssignOp = 4,
			ConcatAssignOp = 5,
			MulAssignOp = 6,
			DivAssignOp = 7,
			ModAssignOp = 8
		};
		AssignCommand(int line, Expr* left, AssignOp op, Expr* right=nullptr);
		virtual ~AssignCommand();

		virtual void execute();
	private:
		Expr* m_left;
		AssignOp m_op;
		Expr* m_right;
};

#endif
