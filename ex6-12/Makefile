CXX = g++
CXXFLAGS = -g3 -Wall -std=c++11

sources = screensz.cc signaldemo2.cc tty_util.cc
target = signaldemo2

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean test
clean:
	rm -rf *.dSYM $(target)

test: $(target)
	./$(target)
