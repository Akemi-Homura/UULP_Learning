CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = pipedemo2.cc
target	= pipedemo2

$(target): $(sources);
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
