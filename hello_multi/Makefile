CXX =clang++
CXXFALGS = -g3 -Wall -pthread -std=c++11

sources = hello_multi.cc
target	= hello_multi

$(target): $(sources)
	$(CXX) $^ $(CXXFALGS) -o $@

clean:
	rm -rf *.dSYM $(target)

.PHONY: test
test: $(target)
	./$(target)
