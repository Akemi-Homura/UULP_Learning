CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = waitdemo1.cc
target	= waitdemo1

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)

.PHONY: test
test: $(target)
	./$(target) 10 | grep "done waiting" | wc -l
	./$(target) 20 | grep "done waiting" | wc -l
	./$(target) 25 | grep "done waiting" | wc -l
	./$(target) 40 | grep "done waiting" | wc -l
	./$(target) 80 | grep "done waiting" | wc -l
	./$(target) 100 | grep "done waiting" | wc -l
