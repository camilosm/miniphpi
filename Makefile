CXX=g++
CXXFLAGS=-g -ggdb -O2 -Wall

TARGET=mphpi
OBJS=mphpi.o lexical/SymbolTable.o lexical/LexicalAnalysis.o syntatic/SyntaticAnalysis.o

all: $(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS)

mphp.o:

lexical/SymbolTable.o: lexical/TokenType.h

lexical/LexicalAnalysis.o: lexical/Lexeme.h lexical/SymbolTable.h

syntatic/SyntaticAnalysis.o: lexical/LexicalAnalysis.h

$(TARGET):	$(OBJS)
			$(CXX) -o $(TARGET) $(OBJS)
.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
