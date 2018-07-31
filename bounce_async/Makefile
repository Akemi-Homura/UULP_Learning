CXX = g++
CXXFLAGS = -g3 -Wall -std=c++11 -l curses

sources = bounce_async.cc time_util.cc
target = bounce_async

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
