CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = smsh4.cc splitline.cc execute.cc controlflow.cc process.cc builtin.cc varlib.cc
target	= smsh

$(target): $(sources);
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf $(target) *.dSYM
