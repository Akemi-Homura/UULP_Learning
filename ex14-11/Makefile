CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11 -pthread

sources = twebserv.cc socklib.cc
target	= twebserv

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
