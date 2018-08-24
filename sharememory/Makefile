CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

target	= shm_tc shm_ts

all: $(target)

shm_tc: shm_tc.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

shm_ts: shm_ts.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY:clean
clean:
	rm -rf *.dSYM $(target)

