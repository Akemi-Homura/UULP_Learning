CXX = g++
CXXFLAGS = -g3 -Wall -std=c++11

target = timeout01 timeout02 test

all: $(target)


timeout01: para_handler.cc timeout01.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

timeout02: timeout02.cc para_handler.cc time_util.cc error_process.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

test: test.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf *.dSYM $(target)
