#ifndef GROUP_RECTANGLES_H
#define GROUP_RECTANGLES_H

typedef struct rectangle {
	float x1, y1, x2, y2;
} Rectangle; 

Rectangle *group_rectangles(Rectangle *rects, int n, float beta, int *size, Rectangle *results = 0);
char *print_rectangle(Rectangle *rect);

#endif
