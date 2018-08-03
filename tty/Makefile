CXX = g++
CXXFLAGS = -g3 -Wall -std=c++11

sources = tty.cc
target  = tty

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
