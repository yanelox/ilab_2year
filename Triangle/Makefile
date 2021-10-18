CXX = g++
CXXFLAGS = -O2 -o $@

triangle.out: main.cpp triangle.h triangle.hpp
	$(CXX) $(CXXFLAGS) $<

check.out: tmain.cpp triangle.h triangle.hpp
	$(CXX) $(CXXFLAGS) $<

debug.out: main.cpp triangle.h triangle.hpp
	$(CXX) $(CXXFLAGS) -g $<
