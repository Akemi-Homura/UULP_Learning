CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

target = timeserv timeclnt

all: $(target)

timeserv: timeserv.cc socklib.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

timeclnt: timeclnt.cc socklib.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
