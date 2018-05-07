.DEFAULT_GOAL := all

COMPILER_TYPE= gnu
CXX = g++
CXXFLAGS = -std=c++0x -Wall

PROG = minderaChallenge.out

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)


.PHONY : all
all : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(PROG)

# To obtain object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# To remove generated files
.PHONY: clean
clean:
	rm -f $(EXEC) $(OBJECTS)