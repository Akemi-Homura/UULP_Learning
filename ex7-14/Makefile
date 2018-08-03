CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

target =  ouch metronome

all: $(target)


ouch: ouch.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

metronome: metronome.cc time_util.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean test
clean:
	rm -rf *.dSYM $(target)

test: $(target)
	./ouch ouch1 4 &
	./ouch ouch2 2 &
	./ouch ouch3 6 &
