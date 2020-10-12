#include "AccessExpr.h"

AccessExpr::AccessExpr(int line, Expr* base, Expr* index)
	:SetExpr(line), m_base(base), m_index(index){
}

AccessExpr::~AccessExpr(){

}

Type* AccessExpr::expr(){

}

void AccessExpr::setExpr(Type* value){

}
