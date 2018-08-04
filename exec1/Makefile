CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = exec1.cc
target  = exec1

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
