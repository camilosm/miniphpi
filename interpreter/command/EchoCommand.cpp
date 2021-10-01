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
			std::cout << v;
			break;
		}
		case Type::StringType: {
			StringValue* sv = (StringValue*) value;
			std::string v = sv->value();
			std::cout << v;
			break;
		}

		case Type::ArrayType: {
			std::cout << "array";
			break;
		}

		default:
			// inalcançável
			break;
	}
}
