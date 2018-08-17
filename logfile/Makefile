CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

target = logfilec logfiled

all: $(target)


logfiled: logfiled.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

logfilec: logfilec.cc
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean test
clean:
	rm -rf *.dSYM $(target)

LOGFILE = vistorlog
test: $(target)
	./logfiled >> $(LOGFILE)&
	./logfilec 'Nice system. Swell software!'
	./logfilec "Testing this log thing."
	./logfilec "Can you read this?"
	cat $(LOGFILE)
