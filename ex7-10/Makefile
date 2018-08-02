CXX = g++
CXXFLAGS = -g3 -Wall -std=c++11 -l curses -lm

sources = hello5.cc screensz.cc
target  = hello5

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf *.dSYM $(target)
