CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = stdinredir1.cc
target	= stdinredir

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
