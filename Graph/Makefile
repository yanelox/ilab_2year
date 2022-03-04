CXX = g++ -std=c++2a
CXXFLAGS = -O2 -o $@

main.out: main.cpp lib/graph.cpp lib/graph.h
	$(CXX) $(CXXFLAGS) $< -Ilib -Ldir
