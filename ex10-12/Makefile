CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = sortfromfile.cc
target	= sortfromfile

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
