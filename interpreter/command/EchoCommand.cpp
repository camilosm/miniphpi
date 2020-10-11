#include <iostream>
#include <cstdio>

#include "EchoCommand.h"

EchoCommand::EchoCommand(int line, Expr* expr):
	Command(line), m_expr(expr){
}

EchoCommand::~EchoCommand(){
}

void EchoCommand::execute(){
	Type* value = m_expr->expr();

	switch (value->type()) {
		case Type::IntegerType:{
			IntegerValue* iv = (IntegerValue*) value;
			int v = iv->value();
			std::cout << v << std::endl;
			break;
		}
		case Type::StringType: {
			StringValue* sv = (StringValue*) value;
			std::string v = sv->value();
			std::cout << v << std::endl;
			break;
		}

		case Type::ArrayType: {
			// TODO: converter
			std::cout << "ArrayType" << std::endl;
			break;
		}

		default:
			// inalcançável
			break;
	}
}
