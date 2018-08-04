CXX = g++
CXXFLAGS = -g3 -Wall -std=c++11 -l curses

sources = titype.cc time_util.cc
target  = titype

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
