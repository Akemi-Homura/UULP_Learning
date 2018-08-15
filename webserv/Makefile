CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = webserv.cc socklib.cc
target	= webserv

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
