#include "ArrayExpr.h"

#include <iostream>


ArrayExpr::ArrayExpr(int line)
	:Expr(line){
}

ArrayExpr::~ArrayExpr(){
}

void ArrayExpr::insert(Expr* key, Expr* value){
	m_array.insert({key, value});
}

Type* ArrayExpr::expr(){
	std::map<std::string,Type*> map;
	std::map<Expr*,Expr*>::iterator it = m_array.begin();
	std::string strkey;
	Type* key;
	Type* value;

	while(it != m_array.end()){
		key = it->first->expr();

		switch(key->type()){
            case Type::IntegerType:{
                IntegerValue* iv = (IntegerValue*) key;
				strkey = std::to_string(iv->value());
                break;
			}
            case Type::StringType:{
                StringValue* sv = (StringValue*) key;
                strkey = sv->value();
                break;
			}
            case Type::ArrayType: {
				printf("%02d: Operação inválida", line());
				exit(1);
                break;
            }
            default:
                // inalcançavel
                break;
        }

		value = it->second->expr();
		map.insert({strkey, value});
		it++;
	}

	ArrayValue* array = new ArrayValue(map);
	return array;

}
