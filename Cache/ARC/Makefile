CXX = g++
CXXFLAGS = -O2 -o $@

arc: main.cpp ARC.h ARC.hpp
	$(CXX) $(CXXFLAGS) $<

debug: main.cpp ARC.h ARC.hpp
	$(CXX) $(CXXFLAGS) $< -g

wall: main.cpp ARC.h ARC.hpp
	$(CXX) $(CXXFLAGS) $< -Wall

gen: gen.cpp ARC.h ARC.hpp
	$(CXX) $(CXXFLAGS) $<
