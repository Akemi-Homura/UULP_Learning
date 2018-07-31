CXX = g++
CXXFLAGS = -g3 -Wall -std=c++11 -l curses

sources = bounce2d01.cc time_util.cc
target = bounce2d

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
