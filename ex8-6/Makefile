CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = forkdemo6.cc
target	= forkdemo6

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
