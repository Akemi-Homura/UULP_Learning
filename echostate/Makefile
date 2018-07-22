CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = echostate.cc
target = echostate

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)

test: $(target)
	./$(target)
	stty -echo
	./$(target)
	stty echo
	./$(target)
