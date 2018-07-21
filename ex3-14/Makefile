CC = clang++
CCFLAGS = -g3

sources = cp03.cc error_process.cc stat_check.cc copy_util.cc
target = cp03

$(target): $(sources)
	$(CC) $(sources) $(CCFLAGS) -o $@

clean:
	rm -rf cp03 *.dSYM

.PHONY: test
test: $(target)
	rm -rf d1 d2;\
	mkdir d1 d2;\
	echo "hello" > d1/a.txt;\
	echo "world" > d2/b.txt;\
	./$(target) d1 d2;\
	rm -rf d3;\
	./$(target) d1 d3
