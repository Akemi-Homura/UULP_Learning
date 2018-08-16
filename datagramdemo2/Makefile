CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

target = dgrecv dgsend

all: $(target)

dgrecv: dgrecv.cc dgram.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

dgsend: dgsend.cc dgram.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
