CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = rotate.cc
target = rotate

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
