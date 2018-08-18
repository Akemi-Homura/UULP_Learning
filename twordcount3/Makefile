CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11 -pthread

sources = twordcount3.cc
target	= twordcount3

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: test clean
clean:
	rm -rf *.dSYM $(target)

test: $(target)
	@echo "hello world woooooooo~" > info1.txt
	@echo "Fuck uestc" > info2.txt
	./$(target) info1.txt info2.txt
	@rm info1.txt info2.txt
