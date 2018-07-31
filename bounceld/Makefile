CXX = g++
CXXFLAGS = -g3 -Wall -std=c++11 -l curses

sources = bounceld.cc
target = bounceld

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf *.dSYM $(target)
