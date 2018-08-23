CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11 -lcurses -pthread

target  = tanclnt tanserv

all: $(target)

tanserv: tanserv.cc socklib.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

tanclnt: tanclnt.cc socklib.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: test clean
clean:
	rm -rf *.dSYM $(target)

test: $(target)
	./tanserv
	./tanclnt 'Fuck UESTC' 'son of bitch' 'Come on baby' 'Can you?'
