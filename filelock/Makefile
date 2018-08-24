CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

target	= file_tc file_ts

all: $(target)

file_ts: file_ts.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

file_tc: file_tc.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY:clean
clean:
	rm -rf *.dSYM $(target)

