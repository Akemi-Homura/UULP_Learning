CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = forkdemo5.cc
target	= forkdemo5

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target) test.txt
