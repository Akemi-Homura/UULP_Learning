CXX = g++
CXXFLAGS = -g3 -Wall -std=c++11 -l curses -lrt

sources = display_util.cc ticker_tape.cc time_util.cc para_handler.cc screensz.cc error_process.cc
target  = ticker_tape

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

.PHONY: clean test
clean:
	rm -rf *.dSYM $(target)

test: $(target)
	./$(target) -s 8 display_util.cc
