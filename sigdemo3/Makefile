CXX = g++
CXXFLAGS = -g3 -Wall -std=c++11

sources = sigdemo3.cc
target = sigdemo3

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf $(target) *.dSYM
