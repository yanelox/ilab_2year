CXX = g++
CXXFLAGS = -O2 -o $@

triangle: main.cpp triangle.h triangle.hpp
	$(CXX) $(CXXFLAGS) $<

check: tmain.cpp triangle.h triangle.hpp
	$(CXX) $(CXXFLAGS) $<

debug: main.cpp triangle.h triangle.hpp
	$(CXX) $(CXXFLAGS) -g $<
