CXX = g++
CXXFLAGS  = -g3 -Wall -std=c++11

targets = sleep1 ticker_demo

all: $(targets)


sleep1: sleep1.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

ticker_demo: ticker_demo.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	rm -rm $(targets) *.dSYM
