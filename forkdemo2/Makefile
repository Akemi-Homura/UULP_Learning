CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = forkdemo2.cc
target  = forkdemo2

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
