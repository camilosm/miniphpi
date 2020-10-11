CXX=g++
CXXFLAGS=-g -ggdb -O2 -Wall

TARGET=mphpi
OBJS=mphpi.o \
	lexical/SymbolTable.o \
	lexical/LexicalAnalysis.o \
	syntatic/SyntaticAnalysis.o \
	interpreter/value/ArrayValue.o \
	interpreter/value/IntegerValue.o \
	interpreter/value/StringValue.o \
	interpreter/expr/ConstExpr.o \
	interpreter/expr/ReadExpr.o \
	interpreter/command/EchoCommand.o \
	interpreter/command/BlocksCommand.o


all: $(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS)

mphp.o:

lexical/SymbolTable.o: lexical/TokenType.h

lexical/LexicalAnalysis.o: lexical/Lexeme.h lexical/SymbolTable.h

syntatic/SyntaticAnalysis.o: lexical/LexicalAnalysis.h

interpreter/value/ArrayValue.o: interpreter/value/Value.h

interpreter/value/IntegerValue.o: interpreter/value/Value.h

interpreter/value/StringValue.o: interpreter/value/Value.h

interpreter/expr/ConstExpr.o: interpreter/expr/Expr.h

interpreter/expr/ReadExpr.o: interpreter/expr/Expr.h interpreter/command/EchoCommand.h interpreter/value/IntegerValue.h interpreter/value/StringValue.h

interpreter/command/EchoCommand.o: interpreter/command/Command.h interpreter/expr/Expr.h interpreter/value/IntegerValue.h interpreter/value/StringValue.h interpreter/value/ArrayValue.h

interpreter/command/BlocksCommand.o: interpreter/command/Command.h

$(TARGET):	$(OBJS)
			$(CXX) -o $(TARGET) $(OBJS)
.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
