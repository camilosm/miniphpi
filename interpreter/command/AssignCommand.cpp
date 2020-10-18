#include "AssignCommand.h"

AssignCommand::AssignCommand(int line, Expr* left, AssignOp op, Expr* right)
	:Command(line), m_left(left), m_op(op), m_right(right){
}

AssignCommand::~AssignCommand(){
	delete m_left;
	delete m_right;
}

void AssignCommand::execute(){

	if(m_op == NoAssignOp)
		return;

	if(!m_left->writable() || m_left->expr()->type() == Type::ArrayType){
		Interruption::semantical(line());
	}

	if(m_left->expr()->type() == Type::StringType)
		if(((StringValue*) m_left->expr())->value() == "")
			((SetExpr*) m_left)->setExpr(new IntegerValue(0));

	if(m_op == StdAssignOp)
		return ((SetExpr*) m_left)->setExpr(m_right->expr());
	else
		if(m_right->expr()->type() == Type::ArrayType){
			//erro
			printf("%02d: Operação inválida", line());
			exit(1);
		}
	switch(m_left->expr()->type()){
		case Type::IntegerType:{
			IntegerValue* lhs = (IntegerValue*) m_left->expr();
			int left_value = lhs->value();
			switch(m_right->expr()->type()){
				case Type::IntegerType:{
					IntegerValue* rhs = (IntegerValue*) m_right->expr();
					int right_value = rhs->value();
					switch(m_op){
						case AddAssignOp:{
							IntegerValue* value = new IntegerValue(left_value+right_value);
							((SetExpr*) m_left)->setExpr(value);
							break;
						}
						case SubAssignOp:{
							IntegerValue* value = new IntegerValue(left_value-right_value);
							((SetExpr*) m_left)->setExpr(value);
							break;
						}
						case ConcatAssignOp:{
							StringValue* value = new StringValue(std::to_string(left_value)+std::to_string(right_value));
							((SetExpr*) m_left)->setExpr(value);
							break;
						}
						case MulAssignOp:{
							IntegerValue* value = new IntegerValue(left_value*right_value);
							((SetExpr*) m_left)->setExpr(value);
							break;
						}
						case DivAssignOp:{
							IntegerValue* value = new IntegerValue(left_value/right_value);
							((SetExpr*) m_left)->setExpr(value);
							break;
						}
						case ModAssignOp:{
							IntegerValue* value = new IntegerValue(left_value%right_value);
							((SetExpr*) m_left)->setExpr(value);
							break;
						}
						default:
							//inalcançável
							break;
					}
					break;
				}
				case Type::StringType:{
					StringValue* sv = (StringValue*) m_right->expr();
					std::string rhs = sv->value();
					if(rhs.find_first_not_of("0123456789") == std::string::npos){
						// rhs = int
						int right_value = std::stoi(rhs);

						switch(m_op){
							case AddAssignOp:{
								IntegerValue* value = new IntegerValue(left_value+right_value);
								((SetExpr*) m_left)->setExpr(value);
								break;
							}
							case SubAssignOp:{
								IntegerValue* value = new IntegerValue(left_value-right_value);
								((SetExpr*) m_left)->setExpr(value);
								break;
							}
							case ConcatAssignOp:{
								StringValue* value = new StringValue(std::to_string(left_value)+std::to_string(right_value));
								((SetExpr*) m_left)->setExpr(value);
								break;
							}
							case MulAssignOp:{
								IntegerValue* value = new IntegerValue(left_value*right_value);
								((SetExpr*) m_left)->setExpr(value);
								break;
							}
							case DivAssignOp:{
								IntegerValue* value = new IntegerValue(left_value/right_value);
								((SetExpr*) m_left)->setExpr(value);
								break;
							}
							case ModAssignOp:{
								IntegerValue* value = new IntegerValue(left_value%right_value);
								((SetExpr*) m_left)->setExpr(value);
								break;
							}
							default:
								//inalcançável
								break;
						}
					}
					else{
						if(m_op == ConcatAssignOp){
							StringValue* value = new StringValue(std::to_string(left_value)+rhs);
							((SetExpr*) m_left)->setExpr(value);
						}
						else
							exit(1);

					}
					break;
				}
				default:
					// inalcançavel
					exit(1);
					break;
			}
			break;
		}
		case Type::StringType:{
			StringValue* sv = (StringValue*) m_left->expr();
			std::string lhs = sv->value();
			if(lhs.find_first_not_of("0123456789") == std::string::npos){
				int left_value = std::stoi(lhs);
				switch(m_right->expr()->type()){
					case Type::IntegerType:{
						IntegerValue* rhs = (IntegerValue*) m_right->expr();
						int right_value = rhs->value();
						switch(m_op){
							case AddAssignOp:{
								IntegerValue* value = new IntegerValue(left_value+right_value);
								((SetExpr*) m_left)->setExpr(value);
								break;
							}
							case SubAssignOp:{
								IntegerValue* value = new IntegerValue(left_value-right_value);
								((SetExpr*) m_left)->setExpr(value);
								break;
							}
							case ConcatAssignOp:{
								StringValue* value = new StringValue(std::to_string(left_value)+std::to_string(right_value));
								((SetExpr*) m_left)->setExpr(value);
								break;
							}
							case MulAssignOp:{
								IntegerValue* value = new IntegerValue(left_value*right_value);
								((SetExpr*) m_left)->setExpr(value);
								break;
							}
							case DivAssignOp:{
								IntegerValue* value = new IntegerValue(left_value/right_value);
								((SetExpr*) m_left)->setExpr(value);
								break;
							}
							case ModAssignOp:{
								IntegerValue* value = new IntegerValue(left_value%right_value);
								((SetExpr*) m_left)->setExpr(value);
								break;
							}
							default:
								//inalcançável
								break;
						}
						break;
					}
					case Type::StringType:{
						StringValue* sv = (StringValue*) m_right->expr();
						std::string rhs = sv->value();
						if(rhs.find_first_not_of("0123456789") == std::string::npos){
							// rhs = int
							int right_value = std::stoi(rhs);

							switch(m_op){
								case AddAssignOp:{
									IntegerValue* value = new IntegerValue(left_value+right_value);
									((SetExpr*) m_left)->setExpr(value);
									break;
								}
								case SubAssignOp:{
									IntegerValue* value = new IntegerValue(left_value-right_value);
									((SetExpr*) m_left)->setExpr(value);
									break;
								}
								case ConcatAssignOp:{
									StringValue* value = new StringValue(std::to_string(left_value)+std::to_string(right_value));
									((SetExpr*) m_left)->setExpr(value);
									break;
								}
								case MulAssignOp:{
									IntegerValue* value = new IntegerValue(left_value*right_value);
									((SetExpr*) m_left)->setExpr(value);
									break;
								}
								case DivAssignOp:{
									IntegerValue* value = new IntegerValue(left_value/right_value);
									((SetExpr*) m_left)->setExpr(value);
									break;
								}
								case ModAssignOp:{
									IntegerValue* value = new IntegerValue(left_value%right_value);
									((SetExpr*) m_left)->setExpr(value);
									break;
								}
								default:
									//inalcançável
									break;
							}
						}
						else{
							if(m_op == ConcatAssignOp){
								StringValue* value = new StringValue(std::to_string(left_value)+rhs);
								((SetExpr*) m_left)->setExpr(value);
							}

						}
						break;
					}
					default:
						// inalcançavel
						exit(1);
						break;
				}
			}
			else{
				if(m_op == ConcatAssignOp){
					std::string rhs;
					if(m_right->expr()->type() == Type::StringType)
						rhs = ((StringValue*) m_right->expr())->value();
					else

						rhs = std::to_string(((IntegerValue*) m_right->expr())->value());

					StringValue* value = new StringValue(lhs+rhs);
					((SetExpr*) m_left)->setExpr(value);
				}
				else
					exit(1);
			}
			break;
		}
		case Type::ArrayType: {
			exit(1);
			break;
		}
		default:
			exit(1);
			// inalcançavel
			break;
	}
}
