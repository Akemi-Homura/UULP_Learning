CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

target = lclnt1 lserv1

all: $(target)


lclnt1: lclnt1.cc dgram.cc lclnt_funcs1.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

lserv1: lserv1.cc dgram.cc lserv_funcs1.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)
