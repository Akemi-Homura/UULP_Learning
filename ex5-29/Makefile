CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = more01.cc more_util.cc screensz.cc
target = more01

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)

test: $(target)
	./$(target) ../ex4-20/ls02.cc more_util.cc
