CXX = g++
CXXFLAGS = -g3 -Wall -std=c++11

sources = sigactdemo.cc
target = sigactdemo

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf $(target) *.dSYM
