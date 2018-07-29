CXX = g++
CXXFLAGS = -g3 -Wall -std=c++11 -l curses

targets = hello1 hello2 hello3 hello4 hello5

all: $(targets)

hello1: hello1.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

hello2: hello2.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

hello3: hello3.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

hello4: hello4.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

hello5: hello5.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY:clean
clean:
	rm -rf $(targets) *.dSYM
