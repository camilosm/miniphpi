#ifndef FOR_EACH_COMMAND_H
#define FOR_EACH_COMMAND_H

#include "Command.h"
#include "../value/ArrayValue.h"
#include "../expr/SetExpr.h"
#include "../expr/Variable.h"
#include "../util/Interruption.h"

class ForeachCommand: public Command{
    public:
        ForeachCommand(int line, Expr* expr, Command* cmds, Variable* key, Variable* value = nullptr);
        virtual ~ForeachCommand();
        virtual void execute();
    private:
        Expr* m_expr;
        Command* m_cmds;
        Variable* m_key;
        Variable* m_value;
};

#endif
