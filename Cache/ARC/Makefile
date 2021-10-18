CXX = g++
CXXFLAGS = -O2 -o $@

arc.out: main.cpp ARC.h ARC.hpp
	$(CXX) $(CXXFLAGS) $<

debug.out: main.cpp ARC.h ARC.hpp
	$(CXX) $(CXXFLAGS) $< -g

wall.out: main.cpp ARC.h ARC.hpp
	$(CXX) $(CXXFLAGS) $< -Wall

gen.out: gen.cpp ARC.h ARC.hpp
	$(CXX) $(CXXFLAGS) $<
