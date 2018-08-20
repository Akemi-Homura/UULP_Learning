CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11 -lcurses -pthread

sources = tanimate.cc
target  = tanimate

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: test clean
clean:
	rm -rf *.dSYM $(target)

test: $(target)
	./$(target) 'Fuck UESTC' 'son of bitch' 'Come on baby' 'Can you?'
