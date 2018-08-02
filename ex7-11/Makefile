CXX = g++
CXXFLAGS  = -g3 -Wall -std=c++11

targets = ticker_demo

ticker_demo: ticker_demo.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	rm -rm $(targets) *.dSYM
