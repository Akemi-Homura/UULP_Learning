CXX = clang++
CXXFLAGS = -g3 -Wall -pthread -std=c++11

sources = incrprint.cc
target	= incrprint

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean test
clean:
	rm -rf *.dSYM $(target)

test: $(target)
	./$(target)
