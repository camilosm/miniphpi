#ifndef IF_COMMAND_H
#define IF_COMMAND_H

#include "Command.h"
#include "../expr/BoolExpr.h"

class IfCommand: public Command{
	public:
		IfCommand(int line, BoolExpr* cond, Command* thenCmds);
		virtual ~IfCommand();
		virtual void addElseCommands(Command* elseCmds);
		virtual void execute();
	private:
		BoolExpr* m_cond;
		Command* m_thenCmds;
		Command* m_elseCmds;
};

#endif
