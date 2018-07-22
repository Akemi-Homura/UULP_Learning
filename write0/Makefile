CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = write0.cc error_process.cc
target = write0

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)

test: $(target)
	./$(target) /dev/ttys001

