CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11 -pthread

sources = twordcount2.cc
target	= twordcount2

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: test clean
clean:
	rm -rf *.dSYM $(target)

test: $(target)
	@echo "hello world woooooooo~" > info1.txt
	@echo "Fuck uestc" > info2.txt
	./$(target) info1.txt info2.txt /etc/passwd
	wc -w info1.txt info2.txt /etc/passwd
	@rm info1.txt info2.txt
