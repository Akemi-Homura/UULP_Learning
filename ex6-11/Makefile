CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = more01.cc more_util.cc screensz.cc tty_util.cc stat_util.cc
target = more01

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)

.PHONY: test stdin
test: $(target)
	./$(target) ../ex4-20/ls02.cc more_util.cc

stdin: $(target)
	cat ../ex4-20/ls02.cc | ./$(target)
