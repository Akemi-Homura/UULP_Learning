CXX = g++
CXXFLAGS = -g3 -Wall -std=c++11 -l curses -pthread

sources = tbounce1d.cc time_util.cc
target = tbounce1d

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf *.dSYM $(target)
