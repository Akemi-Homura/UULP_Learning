CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = forkdemo4.cc
target	= forkdemo4

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
