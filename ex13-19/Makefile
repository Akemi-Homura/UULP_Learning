CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

target = logfilec logfiled

all: $(target)


logfiled: logfiled.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

logfilec: logfilec.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

LOGFILE = vistorlog
TMPFILE = /tmp/logfilesock
.PHONY: clean test
clean:
	rm -rf *.dSYM $(target) $(LOGFILE) $(TMPFILE)

test: $(target)
	@rm -f $(TMPFILE) $(LOGFILE)
	@touch $(LOGFILE)
	./logfiled >> $(LOGFILE)&
	@sleep 1
	./logfilec 'Nice system. Swell software!'
	./logfilec "Testing this log thing."
	./logfilec "Can you read this?"
	cat $(LOGFILE)
	@killall logfiled
