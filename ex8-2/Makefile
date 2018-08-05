CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = forkdemo3.cc
target	= forkdemo3

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
