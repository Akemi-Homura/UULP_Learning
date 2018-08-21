CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = tpwordcount.cc
target	= tpwordcount

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY:clean
clean:
	rm -rf *.dSYM $(target)
