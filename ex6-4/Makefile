CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources_01 = tty_util.cc playagain4_01.cc
sources_02 = tty_util.cc playagain4_02.cc
target = playagain4_01 playagain4_02

all: $(target)

playagain4_01: $(sources_01)
	$(CXX) $^ $(CXXFLAGS) -o $@

playagain4_02: $(sources_01)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
