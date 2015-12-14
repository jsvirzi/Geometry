OPENCVLIBS=$(shell pkg-config --libs opencv)
OPENCVINCS=$(shell pkg-config --cflags opencv)
CFLAGS=-std=gnu++11 

all: test_group_rectangles

test_group_rectangles: test_group_rectangles.c group_rectangles.c
	g++ $(CFLAGS) $(OPENCVINCS) $(INCLUDES) -o test_group_rectangles test_group_rectangles.c group_rectangles.c $(OPENCVLIBS) 

