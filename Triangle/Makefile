CXX = g++
CXXFLAGS = -std=c++17 -O2 -o $@
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXrandr

triangle.out: main.cpp lib/triangle.h lib/triangle.hpp vulkan/vulkan.cpp
	$(CXX) $(CXXFLAGS) $< $(LDFLAGS) -DNDEBUG

check.out: tmain.cpp lib/triangle.h lib/triangle.hpp
	$(CXX) $(CXXFLAGS) $< 

debug.out: main.cpp lib/triangle.h lib/triangle.hpp vulkan/vulkan.cpp
	$(CXX) $(CXXFLAGS) -g $< $(LDFLAGS)
