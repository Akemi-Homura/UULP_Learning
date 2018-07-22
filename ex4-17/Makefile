CC = clang++
CCFLAGS = -g3 -Wall -std=c++11

sources = mv02.cc error_process.cc stat_check.cc
target = mv02

$(target): $(sources)
	$(CC) $(sources) $(CCFLAGS) -o $@

clean:
	rm -rf a.txt b.txt c.txt d1
	rm -rf $(target) *.dSYM

.PHONY: test
test: $(target)
	rm -rf a.txt b.txt c.txt d1
	echo "hee" > a.txt
	echo "eawtat" > c.txt
	mkdir d1
	./$(target) a.txt b.txt
	echo "hee" > a.txt
	./$(target) a.txt c.txt
	echo "hee" > a.txt
	./$(target) a.txt d1
