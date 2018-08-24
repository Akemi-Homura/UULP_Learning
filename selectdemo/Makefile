CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = selectdemo.cc
target	= selectdemo

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY:clean
clean:
	rm -rf *.dSYM $(target)

