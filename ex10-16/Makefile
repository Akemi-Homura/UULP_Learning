CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = isaregfile.cc
target	= isaregfile

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
