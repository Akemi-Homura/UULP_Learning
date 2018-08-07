CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = smsh1.cc splitline.cc execute.cc
target	= smsh

$(target): $(sources);
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf $(target) *.dSYM
