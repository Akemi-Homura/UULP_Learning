CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = uppercase.cc
target = uppercase

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)

test: $(target)
	./$(target)
