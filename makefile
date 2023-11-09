# Complete the following makefile to compile the program and generate the
# executable file main.

CXX = g++
CXXFLAGS = -std=c++11 -Wall 

# Executable names
MAIN = main

.PHONY: all clean

all: $(MAIN)

$(MAIN): main.cpp tsp_genetic_algorithm.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(MAIN)

