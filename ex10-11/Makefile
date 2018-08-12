CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = whotofile.cc
target	= whotofile

$(target): $(sources);
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
