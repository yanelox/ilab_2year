CXX = g++
CXXFLAGS = -O2 -o $@

matrix.out: main.cpp matrix.h matrix.hpp
	$(CXX) $(CXXFLAGS) $<

debug.out: main.cpp matrix.h matrix.hpp
	$(CXX) $(CXXFLAGS) -g $<

gen.out: gen.cpp matrix.hpp matrix.h
	$(CXX) $(CXXFLAGS) $<
