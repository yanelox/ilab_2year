CXX = g++
CXXFLAGS = -O2 -o $@

triangle.out: main.cpp lib/triangle.h lib/triangle.hpp
	$(CXX) $(CXXFLAGS) $<

check.out: tmain.cpp lib/triangle.h lib/triangle.hpp
	$(CXX) $(CXXFLAGS) $<

debug.out: main.cpp lib/triangle.h lib/triangle.hpp
	$(CXX) $(CXXFLAGS) -g $<
