CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = sigdemo2.cc
target  = sigdemo2

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
