# use g++ with C++11 support
CXXFLAGS?=-Wall -pedantic -O0 -std=c++11

all: remove-chars

remove-chars: remove-chars.o
	g++ -o remove-chars $(CXXFLAGS) remove-chars.o

remove-chars.o: remove-chars.cpp
	g++ -c $(CXXFLAGS) remove-chars.cpp