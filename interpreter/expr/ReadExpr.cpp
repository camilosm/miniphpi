#include "ReadExpr.h"

ReadExpr::ReadExpr(int line, Expr* msg):Expr(line), m_msg(msg){
}

ReadExpr::~ReadExpr(){
}

Type* ReadExpr::expr(){
	EchoCommand* echo = new EchoCommand(getLine(), m_msg);
	echo->execute();
	std::string input;
	std::cin >> input;

	for(int i=0; i<(int)input.length();i++)
		if(!isdigit(input[i])){
			StringValue* str = new StringValue(input);
			return str;
		}

	IntegerValue* integer = new IntegerValue(stoi(input));
	return integer;
}
