CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -pedantic $(INCLUDES)

exec: main.cc
	$(CXX) $(CXXFLAGS) $< -o $@

.DEFAULT_GOAL := exec