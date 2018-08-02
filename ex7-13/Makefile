CXX = g++
CXXFLAGS = -g3 -Wall -std=c++11

target = timeout01

$(target): para_handler.cc timeout01.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf *.dSYM $(target)
