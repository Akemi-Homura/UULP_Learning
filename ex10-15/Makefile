CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = progtee.cc
target	= progtee

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
