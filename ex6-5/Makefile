CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = rotate.cc tty_util.cc
target = rotate

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
