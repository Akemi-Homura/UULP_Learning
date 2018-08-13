CXX = clang++
CXXFLANGS = -g3 -Wall -std=c++11

target = rls rlsd

all: $(target)

rls: rls.cc
	$(CXX) $^ $(CXXFLANGS) -o $@

rlsd: rlsd.cc
	$(CXX) $^ $(CXXFLANGS) -o $@

clean:
	rm -rf *.dSYM $(target)
