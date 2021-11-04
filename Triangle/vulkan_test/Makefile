CXX = g++
CFLAGS = -std=c++17 -O2 -o $@
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXrandr

VulkanTest: main.cpp
	$(CXX) $(CFLAGS) $< $(LDFLAGS) -DNDEBUG

debug: main.cpp
	$(CXX) $(CFLAGS) $< $(LDFLAGS)

.PHONY: test clean

test: VulkanTest
	./VulkanTest

clean:
	rm -f VulkanTest debug