CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11 -l curses

sources = psh2.cc
target	= psh2

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
