CXX=g++
CXXFLAGS=-g -ggdb -O2 -Wall

TARGET=mphpi
OBJS=mphpi.o \
    lexical/SymbolTable.o \
    lexical/LexicalAnalysis.o \
    syntatic/SyntaticAnalysis.o \
    interpreter/util/Interruption.o \
    interpreter/util/Memory.o \
    interpreter/value/ArrayValue.o \
    interpreter/value/IntegerValue.o \
    interpreter/value/StringValue.o \
    interpreter/expr/AccessExpr.o \
    interpreter/expr/ArrayExpr.o \
    interpreter/expr/BinaryExpr.o \
    interpreter/expr/CompositeBoolExpr.o \
    interpreter/expr/ConstExpr.o \
    interpreter/expr/NotBoolExpr.o \
    interpreter/expr/ReadExpr.o \
    interpreter/expr/SingleBoolExpr.o \
    interpreter/expr/UnaryExpr.o \
    interpreter/expr/Variable.o \
    interpreter/expr/VarVarExpr.o \
    interpreter/command/AssignCommand.o \
    interpreter/command/BlocksCommand.o \
    interpreter/command/EchoCommand.o \
    interpreter/command/ForeachCommand.o \
    interpreter/command/IfCommand.o \
    interpreter/command/WhileCommand.o

all: $(TARGET)
	@echo "Done!"

clean:
	@echo "Cleaning..."
	@rm -rf $(TARGET) $(OBJS)
	@echo "Done!"

test: $(TARGET)
	@echo "Testing:"
	@(cd tests; ./test.sh)
	@echo "Done!"

debug: $(TARGET)
	@echo "Debugging:"
	@(cd tests; ./debug.sh)
	@echo "Done!"

mphpi.o:

lexical/SymbolTable.o: lexical/TokenType.h

lexical/LexicalAnalysis.o: lexical/Lexeme.h lexical/SymbolTable.h

syntatic/SyntaticAnalysis.o: lexical/LexicalAnalysis.h interpreter/expr/AccessExpr.h interpreter/expr/ArrayExpr.h interpreter/expr/BinaryExpr.h interpreter/expr/CompositeBoolExpr.h interpreter/expr/ConstExpr.h interpreter/expr/NotBoolExpr.h interpreter/expr/ReadExpr.h interpreter/expr/SingleBoolExpr.h interpreter/expr/UnaryExpr.h interpreter/expr/Variable.h interpreter/expr/VarVarExpr.h interpreter/value/IntegerValue.h interpreter/value/StringValue.h interpreter/command/AssignCommand.h interpreter/command/BlocksCommand.h interpreter/command/Command.h interpreter/command/EchoCommand.h interpreter/command/ForeachCommand.h interpreter/command/IfCommand.h interpreter/command/WhileCommand.h

interpreter/util/Interruption.o: interpreter/util/Interruption.h

interpreter/util/Memory.o: interpreter/util/Memory.h interpreter/expr/SetExpr.h

interpreter/value/ArrayValue.o: interpreter/value/Value.h

interpreter/value/IntegerValue.o: interpreter/value/Value.h

interpreter/value/StringValue.o: interpreter/value/Value.h

interpreter/expr/AccessExpr.o: interpreter/expr/SetExpr.h interpreter/value/ArrayValue.h interpreter/util/Memory.h interpreter/util/Interruption.h

interpreter/expr/ArrayExpr.o: interpreter/expr/Expr.h interpreter/value/IntegerValue.h interpreter/value/StringValue.h interpreter/value/ArrayValue.h

interpreter/expr/BinaryExpr.o: interpreter/expr/Expr.h interpreter/value/IntegerValue.h interpreter/value/StringValue.h interpreter/value/ArrayValue.h interpreter/util/Interruption.h

interpreter/expr/CompositeBoolExpr.o: interpreter/expr/BoolExpr.h interpreter/util/Interruption.h

interpreter/expr/ConstExpr.o: interpreter/expr/Expr.h

interpreter/expr/NotBoolExpr.o: interpreter/expr/BoolExpr.h

interpreter/expr/ReadExpr.o: interpreter/expr/Expr.h interpreter/command/EchoCommand.h interpreter/value/IntegerValue.h interpreter/value/StringValue.h

interpreter/expr/SingleBoolExpr.o: interpreter/expr/BoolExpr.h interpreter/util/Interruption.h

interpreter/expr/UnaryExpr.o: interpreter/expr/SetExpr.h interpreter/value/IntegerValue.h interpreter/value/StringValue.h interpreter/util/Interruption.h

interpreter/expr/Variable.o: interpreter/expr/SetExpr.h interpreter/util/Interruption.h

interpreter/expr/VarVarExpr.o: interpreter/expr/VarVarExpr.h interpreter/util/Memory.h interpreter/util/Interruption.h

interpreter/command/AssignCommand.o: interpreter/expr/Expr.h interpreter/expr/Variable.h

interpreter/command/BlocksCommand.o: interpreter/command/BlocksCommand.h interpreter/command/Command.h

interpreter/command/EchoCommand.o: interpreter/command/EchoCommand.h interpreter/command/Command.h interpreter/expr/Expr.h interpreter/value/IntegerValue.h interpreter/value/StringValue.h interpreter/value/ArrayValue.h

interpreter/command/ForeachCommand.o: interpreter/command/ForeachCommand.h interpreter/command/Command.h interpreter/value/ArrayValue.h interpreter/expr/SetExpr.h interpreter/expr/Variable.h interpreter/util/Interruption.h

interpreter/command/IfCommand.o: interpreter/command/ForeachCommand.h interpreter/command/Command.h interpreter/expr/BinaryExpr.h

interpreter/command/WhileCommand.o: interpreter/command/WhileCommand.h interpreter/expr/BoolExpr.h

$(TARGET): $(OBJS)
	@echo "Linking..."
	@$(CXX) -o $(TARGET) $(OBJS)

.cpp.o:
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
