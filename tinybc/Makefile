CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = tinybc.cc
target	= tinybc

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
