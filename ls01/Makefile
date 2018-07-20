CCX = clang++
CCXFLAGS = -g3 -Wall -std=c++11

sources = ls01.cc ls02.cc

all: ls01 ls02

ls01: ls01.cc
	$(CCX) $< $(CCXFLAGS) -o $@

ls02: ls02.cc
	$(CCX) $< $(CCXFLAGS) -o $@

clean:
	rm -rf $(sources:.cc=.dSYM)
	rm -f $(sources:%.cc=%)
