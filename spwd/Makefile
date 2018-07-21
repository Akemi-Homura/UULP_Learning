CCX = clang++
CCXFLAGS = -g -Wall -std=c++11

sources = inode_util.cc spwd.cc spwd_util.cc error_process.cc
target = spwd

$(target): $(sources)
	$(CCX) $^ $(CCXFLAGS) -o $@

clean:
	rm -rf $(target) *.dSYM
