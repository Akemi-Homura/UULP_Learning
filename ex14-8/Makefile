CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = tpwordcount.cc
target	= tpwordcount

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY:clean test
clean:
	rm -rf *.dSYM $(target)

test: $(target)
	@echo "hello world" > info1.txt
	@echo "fuck uestc fsdfasdffa" > info2.txt
	@sleep 1
	./$(target) info1.txt info2.txt /etc/passwd
	wc -w info1.txt info2.txt /etc/passwd
	@rm info1.txt info2.txt
