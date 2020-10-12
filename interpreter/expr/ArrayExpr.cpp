#include "ArrayExpr.h"

ArrayExpr::ArrayExpr(int line):Expr(line){
}

ArrayExpr::~ArrayExpr(){
}

void ArrayExpr::insert(Expr* key, Expr* value){
	m_array.insert({key, value});
}

Type* ArrayExpr::expr(){
	std::map<std::string,Type*> arrayvalue;
	std::map<Expr*,Expr*>::iterator it = m_array.begin();
	std::string key;
	Type* keytype;
	Type* value;


	while(it != m_array.end()){
		keytype = it->first->expr();

		switch (keytype->type()) {
            case Type::IntegerType: {
                IntegerValue* iv = (IntegerValue*) keytype;
				key = std::to_string(iv->value());
                break;
            }
            case Type::StringType: {
                StringValue* sv = (StringValue*) keytype;
                key = sv->value();
                break;
            }
            case Type::ArrayType: {
                //erro semantico
				return nullptr;
                break;
            }
            default:
                // inalcançavel
                break;
        }

		arrayvalue.insert({key, value});
		it++;
	}

	ArrayValue* array = new ArrayValue(arrayvalue);
	return array;
}
