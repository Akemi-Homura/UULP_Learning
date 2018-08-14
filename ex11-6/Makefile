CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = tinybc.cc
target	= tinybc

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)

.PHONY: test
test: $(target)
	printf "2+2\n4*4\n2^32\n" | ./$(target)
