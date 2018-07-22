CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

targets = echostate setecho

all: $(targets)

echostate: echostate.cc error_process.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

setecho: setecho.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM *.o $(targets)

test: $(targets)
	./echostate
	./setecho n
	./echostate
	./setecho ysadf
	./echostate
