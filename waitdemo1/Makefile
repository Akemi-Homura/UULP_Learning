CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = waitdemo1.cc
target	= waitdemo1

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
