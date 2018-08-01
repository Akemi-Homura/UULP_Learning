CXX = g++
CXXFLAGS = -g3 -Wall -std=c++11 -l curses

sources = hello1.cc
target = hello1

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
