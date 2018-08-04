CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = psh1.cc
target  = psh1

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
