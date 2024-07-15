#ifndef EXPR_H
#define EXPR_H

#include "../value/Value.h"
#include "../value/IntegerValue.h"
#include "../value/StringValue.h"

class Expr{
    public:
        virtual ~Expr(){}
        int line() const{
            return m_line;
        }
        virtual Type* expr() = 0;
        virtual bool writable() { return false;}
    protected:
        Expr(int line): m_line(line){}

    private:
        int m_line;
};

#endif
