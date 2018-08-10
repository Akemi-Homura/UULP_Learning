CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = pipedemo.cc
target	= pipedemo

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
