CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = screen_size.cc
target = screen_size

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)

.PHONY: test
test: $(target)
	./$(target)
