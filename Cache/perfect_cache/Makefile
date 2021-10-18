CXX = g++
CXXFLAGS = -O2 -o $@

beladi: main.cpp prfct.h prfct.hpp
	$(CXX) $(CXXFLAGS) $<

debug: main.cpp prfct.h prfct.hpp
	$(CXX) $(CXXFLAGS) -g $<
