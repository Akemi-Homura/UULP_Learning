CXX = g++
CXXFLAGS = -g3 -Wall -std=c++11 -l curses

sources = bounce1d.cc time_util.cc
target = bounce1d

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf *.dSYM $(target)
