CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = tty_util.cc playagain4.cc
target = playagain4

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
