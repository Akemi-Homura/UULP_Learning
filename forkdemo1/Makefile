CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = forkdemo1.cc
target  = forkdemo1

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
