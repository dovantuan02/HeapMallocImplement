CROSS_COMPILE=

CXX = $(CROSS_COMPILE)g++
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
STRIP = $(CROSS_COMPILE)strip

CXXFLAGS = -std=c++11 -Wall -I.
LDLIBS = -lpthread -L/usr/local/lib  # Specify the library path and name

# sudo export LD_LIBRARY_PATH=/usr/local/lib

main: Malloc_implement.o heap_4.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)


# Specific rules for main and Malloc_implement
Malloc_implement.o: Malloc_implement.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

heap_4.o: heap_4.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Targets
all: main

clean:
	rm -f Malloc_implement.o Malloc_implement