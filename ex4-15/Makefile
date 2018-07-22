CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = mkdirp.cc mkdirp_util.cc umask.cc error_process.cc
target = mkdirp

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)

test:
	rm -rf d[1-7]
	./$(target) d1 d2
	./$(target) -p d3/d4
	./$(target) -p d4/d5/d6/d7/d8 d5/d6 d7
	./$(target) d1/d2
	./$(target) -p d2/d3/d4
	./$(target) -p `pwd`/d8/d9
