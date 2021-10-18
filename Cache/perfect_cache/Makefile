CXX = g++
CXXFLAGS = -O2 -o $@

beladi.out: main.cpp prfct.h prfct.hpp
	$(CXX) $(CXXFLAGS) $<

debug.out: main.cpp prfct.h prfct.hpp
	$(CXX) $(CXXFLAGS) -g $<
