CXX = g++
CXXFLAGS = -std=c++20 -Wall -fsanitize=address,leak -g
LDFLAGS = -fsanitize=address,leak

.PHONY: all clean

all: l7

l7: main.cpp Hash.hpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.cpp -o l7
	

clean:
	rm -f *.o l7