#include "BinaryExpr.h"

BinaryExpr::BinaryExpr(int line, Expr* left, BinaryOp op, Expr*right)
	:Expr(line), m_left(left), m_op(op), m_right(right){
}

BinaryExpr::~BinaryExpr(){
	delete m_right;
	delete m_left;
}

Type* BinaryExpr::expr(){
	if(m_left->expr()->type() == Type::ArrayType || m_right->expr()->type() == Type::ArrayType)
		Interruption::semantical(line());
	if(m_op == ConcatOp){
		std::string left, right;
		if(m_left->expr()->type() == Type::IntegerType)
			left = std::to_string(((IntegerValue*)m_left->expr())->value());
		else
			left = ((StringValue*)m_left->expr())->value();

		if(m_right->expr()->type() == Type::IntegerType)
			right = std::to_string(((IntegerValue*)m_right->expr())->value());
		else
			right = ((StringValue*)m_right->expr())->value();

		return new StringValue(left+right);
	}
	else{
		int left=0;
		if(m_left->expr()->type() == Type::StringType){
			std::string str = ((StringValue*)m_left->expr())->value();
			if(str == "")
				left = 0;
			else if(str.find_first_not_of("0123456789") == std::string::npos)
				left = std::stoi(str);
			else
				Interruption::semantical(1111);
		}
		else
			left = ((IntegerValue*)m_left->expr())->value();

		int right=0;
		if(m_right->expr()->type() == Type::StringType){
			std::string str = ((StringValue*)m_right->expr())->value();
			if(str == "")
				right = 0;
			else if(str.find_first_not_of("0123456789") == std::string::npos)
				right = std::stoi(str);
			else
				Interruption::semantical(line());
		}
		else
			right = ((IntegerValue*)m_right->expr())->value();

		switch(m_op){
			case AddOp:
				return new IntegerValue(left+right);
				break;

			case SubOp:
				return new IntegerValue(left-right);
				break;

			case MulOp:
				return new IntegerValue(left*right);
				break;

			case DivOp:
				return new IntegerValue(left/right);
				break;

			case ModOp:
				return new IntegerValue(left%right);
				break;

		default:
			Interruption::semantical(line());
			break;
		}
	}
	return nullptr;
}
