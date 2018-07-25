CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = sigdemo1.cc
target =  sigdemo1

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
