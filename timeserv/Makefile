CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

target	= timeserv timeclnt

all: $(target)

timeserv: timeserv.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

timeclnt: timeclnt.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean test
clean:
	rm -rf *.dSYM $(target)

test: $(target)
	./timeserv &
	./timeclnt `hostname` 13000
