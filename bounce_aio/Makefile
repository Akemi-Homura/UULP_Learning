CXX = g++
CXXFLAGS = -g3 -Wall -std=c++11 -l curses -lrt

sources = bounce_aio.cc time_util.cc
target = bounce_aio

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean test
clean:
	rm -rf *.dSYM $(target)

test: $(target)
	./$(target)
