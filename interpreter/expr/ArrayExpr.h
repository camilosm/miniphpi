#ifndef ARRAY_EXPR_H
#define ARRAY_EXPR_H

#include <map>
#include <iterator>

#include "Expr.h"
#include "../value/IntegerValue.h"
#include "../value/StringValue.h"
#include "../value/ArrayValue.h"

class ArrayExpr: public Expr{
	public:
		ArrayExpr(int line);
		virtual ~ArrayExpr();

		virtual void insert(Expr* key, Expr* value);
		virtual Type* expr();
	private:
		std::map<Expr*,Expr*> m_array;
};


#endif
