#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <map>

#include "../util/Memory.h"
#include "SetExpr.h"

class Variable: public SetExpr{
    public:
        Variable(int line, const std::string& name);
        virtual ~Variable();

        const std::string& getName() { return m_name; }
        virtual Type* expr();
        void setExpr(Type* value);

    private:
        const std::string m_name;
};

#endif
