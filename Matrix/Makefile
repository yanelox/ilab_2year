CXX = g++
CXXFLAGS = -O2 -o $@

matrix.out: main.cpp lib/matrix.h lib/matrix.hpp
	$(CXX) $(CXXFLAGS) $< 

debug.out: main.cpp lib/matrix.h lib/matrix.hpp
	$(CXX) $(CXXFLAGS) -g $<

gen.out: gen.cpp lib/matrix.hpp lib/matrix.h
	$(CXX) $(CXXFLAGS) $<
