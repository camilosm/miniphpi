CXX=g++
CXXFLAGS=-g -ggdb -O2 -Wall

TARGET=mphpi
OBJS=mphpi.o

all: $(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS)

mphp.o:

$(TARGET):	$(OBJS)
			$(CXX) -o $(TARGET) $(OBJS)
.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
