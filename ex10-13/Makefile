CXX = clang++
CXXFLAGS = -g3 -Wall -std=c++11

sources = pipe.cc
target	= pipe

$(target): $(sources)
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm -rf *.dSYM $(target)

test: $(target)
	@echo test pipe...
	@zsh test.sh
