CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = timeserv.cc
target	= timeserv

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
