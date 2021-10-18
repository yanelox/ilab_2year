CXX = g++
CXXFLAGS = -O2 -o $@

matrix: main.cpp matrix.h matrix.hpp
	$(CXX) $(CXXFLAGS) $<

debug: main.cpp matrix.h matrix.hpp
	$(CXX) $(CXXFLAGS) -g $<

gen: gen.cpp matrix.hpp matrix.h
	$(CXX) $(CXXFLAGS) $<
