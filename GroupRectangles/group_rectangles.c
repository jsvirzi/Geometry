#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "group_rectangles.h"

#undef DEBUG

typedef struct extended_rectangle {
	Rectangle *rect;
	struct extended_rectangle *prev, *next; /* for linked list */
	float area;
	float intersection_threshold;
	int id;
} ExtendedRectangle;

typedef struct line {
	float x1, y1, x2, y2;
} Line; 

typedef struct point {
	float x, y;
} Point;

bool is_interior(Point *p, Rectangle *rect);

float area(Rectangle *rect) {
	return (rect->y2 - rect->y1) * (rect->x2 - rect->x1);
}

float area(Point *p, int n) {
	int i;
	float acc = 0.0;
	for(i=0;i<(n-1);++i) {
		acc += (p[i+1].x + p[i].x) * (p[i+1].y - p[i].y);
		printf("area: pt(%d) = (%.1f, %.1f). acc = %f\n", i, p[i].x, p[i].y, acc);
	}
	acc += (p[0].x + p[i].x) * (p[0].y - p[i].y);
	printf("area: pt(%d) = (%.1f, %.1f). acc = %f\n", i, p[i].x, p[i].y, acc);
	return 0.5 * acc;
}

char *print_rectangle(Rectangle *rect) {
	static char str[64]; 
	snprintf(str, sizeof(str), "(%.1f, %.1f) x (%.1f, %.1f)", rect->x1, rect->y1, rect->x2, rect->y2);
	return str;
}

bool intersect(Line *linea, Line *lineb, Point *p, int *type) {
	float x1a = linea->x1, x2a = linea->x2, y1a = linea->y1, y2a = linea->y2; 
	float x1b = lineb->x1, x2b = lineb->x2, y1b = lineb->y1, y2b = lineb->y2; 

#ifdef DEBUG
	printf("intersect(line=((%.1f,%.1f),(%.1f,%.1f)) X line=((%.1f,%.1f),(%.1f,%.1f))\n", x1a, y1a, x2a, y2a, x1b, y1b, x2b, y2b);
#endif

	float t;

/* are the lines horizontal or vertical */
	bool linea_hor = false, linea_ver = false;
	if(x1a == x2a) { linea_ver = true; }
	else if(y1a == y2a) { linea_hor = true; }

	bool lineb_hor = false, lineb_ver = false;
	if(x1b == x2b) { lineb_ver = true; }
	else if(y1b == y2b) { lineb_hor = true; }

	/* if both lines are either horizontal or vertical, processing is straightforward */
	if(linea_hor && lineb_ver) {

	/* order the intervals */
		if(x2a < x1a) { t = x2a; x2a = x1a; x1a = t; }
		if(y2b < y1b) { t = y2b; y2b = y1b; y1b = t; }

		if((y1b < y1a && y2a < y2b) && (x1a < x1b && x2b < x2a)) {
			p->x = x1b;
			p->y = y1a;
			*type = 0;
			return true;
		}

		if(((y1a == y1b) || (y2a == y2b)) && (x1a < x1b && x2b < x2a)) {
			p->x = x1b;
			p->y = y1a;
			*type = 1;
			return true;
		}

		if(((x1a == x1b) || (x2a == x2b)) && (y1b < y1a && y2a < y2b)) {
			p->x = x1b;
			p->y = y1a;
			*type = 1;
			return true;
		}

	} else if(lineb_hor && linea_ver) {

	/* order the intervals */
		if(y2a < y1a) { t = y2a; y2a = y1a; y1a = t; }
		if(x2b < x1b) { t = x2b; x2b = x1b; x1b = t; }

		if((y1a < y1b && y2b < y2a) && (x1b < x1a && x2a < x2b)) {
			p->x = x1a;
			p->y = y1b;
			*type = 0;
			return true;
		}

		if(((x1b == x1a) || (x2b == x2a)) && (y1a < y1b && y2b < y2a)) {
			p->x = x1a;
			p->y = y1b;
			*type = 1;
			return true;
		}

		if(((y1b == y1a) || (y2b == y2a)) && (x1b < x1a && x2a < x2b)) {
			p->x = x1a;
			p->y = y1b;
			*type = 1;
			return true;
		}
	}
	return false;
}

/* assume ordered in x, y? */
float intersection(Rectangle *recta, Rectangle *rectb) {
	float result = 0.0;
	float xmin = recta->x1;
	float xmax = xmin;
	if(recta->x2 < xmin) xmin = recta->x2;
	if(recta->x2 > xmax) xmax = recta->x2;
	if(rectb->x1 < xmin) xmin = rectb->x1;
	if(rectb->x1 > xmax) xmax = rectb->x1;
	if(rectb->x2 < xmin) xmin = rectb->x2;
	if(rectb->x2 > xmax) xmax = rectb->x2;
	float ymin = recta->y1;
	float ymax = ymin;
	if(recta->y2 < ymin) ymin = recta->y2;
	if(recta->y2 > ymax) ymax = recta->y2;
	if(rectb->y1 < ymin) ymin = rectb->y1;
	if(rectb->y1 > ymax) ymax = rectb->y1;
	if(rectb->y2 < ymin) ymin = rectb->y2;
	if(rectb->y2 > ymax) ymax = rectb->y2;
	Rectangle uber_rectangle = { xmin, ymin, xmax, ymax };

	Line line1a = { recta->x1, recta->y1, recta->x1, recta->y2 }; /* vertical */
	Line line1b = { recta->x2, recta->y1, recta->x2, recta->y2 }; /* vertical */
	Line line1c = { recta->x1, recta->y1, recta->x2, recta->y1 }; /* horizontal */
	Line line1d = { recta->x1, recta->y2, recta->x2, recta->y2 }; /* horizontal */

	Line line2a = { rectb->x1, rectb->y1, rectb->x1, rectb->y2 }; /* vertical */
	Line line2b = { rectb->x2, rectb->y1, rectb->x2, rectb->y2 }; /* vertical */
	Line line2c = { rectb->x1, rectb->y1, rectb->x2, rectb->y1 }; /* horizontal */
	Line line2d = { rectb->x1, rectb->y2, rectb->x2, rectb->y2 }; /* horizontal */

	Point p;
	Point xpoints[12];
	Point tpoints[12];

	xpoints[0] = { recta->x1, recta->y1 };
	xpoints[1] = { recta->x1, recta->y2 };
	xpoints[2] = { recta->x2, recta->y1 };
	xpoints[3] = { recta->x2, recta->y2 };

	xpoints[4] = { rectb->x1, rectb->y1 };
	xpoints[5] = { rectb->x1, rectb->y2 };
	xpoints[6] = { rectb->x2, rectb->y1 };
	xpoints[7] = { rectb->x2, rectb->y2 };

	int xindex = 8, tindex = 0, type;

	if(intersect(&line1a, &line2c, &p, &type)) { 
#ifdef DEBUG
		printf("intersection = (%.1f, %.1f) is type %d\n", p.x, p.y, type);
#endif
		if(type == 0) xpoints[xindex++] = p;
		else if(type == 1) tpoints[tindex++] = p;
	};
	if(intersect(&line1a, &line2d, &p, &type)) { 
#ifdef DEBUG
		printf("intersection = (%.1f, %.1f) is type %d\n", p.x, p.y, type);
#endif
		if(type == 0) xpoints[xindex++] = p;
		else if(type == 1) tpoints[tindex++] = p;
	};
	if(intersect(&line1b, &line2c, &p, &type)) { 
#ifdef DEBUG
		printf("intersection = (%.1f, %.1f) is type %d\n", p.x, p.y, type);
#endif
		if(type == 0) xpoints[xindex++] = p;
		else if(type == 1) tpoints[tindex++] = p;
	};
	if(intersect(&line1b, &line2d, &p, &type)) { 
#ifdef DEBUG
		printf("intersection = (%.1f, %.1f) is type %d\n", p.x, p.y, type);
#endif
		if(type == 0) xpoints[xindex++] = p;
		else if(type == 1) tpoints[tindex++] = p;
	};
	if(intersect(&line1c, &line2a, &p, &type)) { 
#ifdef DEBUG
		printf("intersection = (%.1f, %.1f) is type %d\n", p.x, p.y, type);
#endif
		if(type == 0) xpoints[xindex++] = p;
		else if(type == 1) tpoints[tindex++] = p;
	};
	if(intersect(&line1c, &line2b, &p, &type)) { 
#ifdef DEBUG
		printf("intersection = (%.1f, %.1f) is type %d\n", p.x, p.y, type);
#endif
		if(type == 0) xpoints[xindex++] = p;
		else if(type == 1) tpoints[tindex++] = p;
	};
	if(intersect(&line1d, &line2a, &p, &type)) { 
#ifdef DEBUG
		printf("intersection = (%.1f, %.1f) is type %d\n", p.x, p.y, type);
#endif
		if(type == 0) xpoints[xindex++] = p;
		else if(type == 1) tpoints[tindex++] = p;
	};
	if(intersect(&line1d, &line2b, &p, &type)) { 
#ifdef DEBUG
		printf("intersection = (%.1f, %.1f) is type %d\n", p.x, p.y, type);
#endif
		if(type == 0) xpoints[xindex++] = p;
		else if(type == 1) tpoints[tindex++] = p;
	};

#ifdef DEBUG
	printf("%d x-points. %d t-points\n", xindex, tindex);
	printf("uber rectangle = %s\n", print_rectangle(&uber_rectangle));
#endif

	int n = 0;
	Point pts[12];

	for(int i=0;i<xindex;++i) {
		bool flag = is_interior(&xpoints[i], &uber_rectangle); 
#ifdef DEBUG
		// printf("point=(%.1f,%.1f) is %s\n", xpoints[i].x, xpoints[i].y, flag ? "inside" : "outside");
#endif
		if(flag) pts[n++] = xpoints[i];
	}

	for(int i=0;i<tindex;++i) { pts[n++] = tpoints[i]; }

	if(n == 4) {
		// printf("final area = %f\n", area(pts, n));

		double xmin = pts[0].x, ymin = pts[0].y, xmax = xmin, ymax = ymin;

		for(int i=1;i<n;++i) {
			double x = pts[i].x, y = pts[i].y;
			if(x < xmin) xmin = x;
			if(x > xmax) xmax = x;
			if(y < ymin) ymin = y;
			if(y > ymax) ymax = y;
		}

		result = (ymax - ymin) * (xmax - xmin);
#if 0
		printf("final area = %f\n", result);
		printf("basic area = %f\n", area0);

		p = pts[1];
		pts[1] = pts[2];
		pts[2] = p;

		p = pts[0];
		pts[0] = pts[1];
		pts[1] = pts[2];
		pts[2] = pts[3];
		pts[3] = p;

		printf("final area = %f\n", area(pts, n));
#endif
	}

	return result;
}

/*
 * this following algorithm works for our purposes, because we are working with the simplest type of rectangle.
 * namely, our rectangles have vertical and horizontal edges. this just checks that our coordinates are within
 * the rectangular bounds
 */
bool is_interior(Point *p, Rectangle *rect) {

/* search for T intersections */
#ifdef DEBUG
	printf("is_interior(P=(%.1f,%.1f), R=(%.1f,%.1f)x(%.1f,%.1f))", p->x, p->y, rect->x1, rect->y1, rect->x2, rect->y2);
#endif

	bool x_ok = (rect->x1 < p->x) && (p->x < rect->x2);
	bool y_ok = (rect->y1 < p->y) && (p->y < rect->y2);

	return x_ok && y_ok;
}

#ifdef ALGORITHMB

/*
 * this algorithm checks for an odd/even number of polygon edge crossings
 */
bool is_interior(Point *p, Rectangle *rect) {

/* search for T intersections */
#ifdef DEBUG
	printf("is_interior(P=(%.1f,%.1f), R=(%.1f,%.1f)x(%.1f,%.1f))", p->x, p->y, rect->x1, rect->y1, rect->x2, rect->y2);
#endif

	return false; /* dummied out */

#endif

#ifdef ALGORITHMA
/*
 * this is an inefficient method to calculate if a point is in the interior of a polygon
 * primarily due to the arctangent function called. there are different algorithms
 * that can be exploited and make this more efficient, including using a lookup table
 */
bool is_interior(Point *p, Rectangle *rect) {

/* search for T intersections */
#ifdef DEBUG
	printf("is_interior(P=(%.1f,%.1f), R=(%.1f,%.1f)x(%.1f,%.1f))", p->x, p->y, rect->x1, rect->y1, rect->x2, rect->y2);
	printf("searching for T intersections\n");
#endif
	bool fx1 = (p->x == rect->x1);
	bool fx2 = (p->x == rect->x2);
	bool fy1 = (p->y == rect->y1);
	bool fy2 = (p->y == rect->y2);

	if(fx1 || fx2 || fy1 || fy2) return false;

	float xa = rect->x2 - p->x; 
	float ya = rect->y2 - p->y;
	float xb = rect->x1 - p->x; 
	float yb = rect->y2 - p->y;
	float s1 = (xa * yb - ya * xb);
	float c1 = (xa * xb + ya * yb);

	xa = xb;
	ya = yb;
	xb = rect->x1 - p->x; 
	yb = rect->y1 - p->y;
	float s2 = (xa * yb - ya * xb);
	float c2 = (xa * xb + ya * yb);

	xa = xb;
	ya = yb;
	xb = rect->x2 - p->x; 
	yb = rect->y1 - p->y;
	float s3 = (xa * yb - ya * xb);
	float c3 = (xa * xb + ya * yb);

	xa = xb;
	ya = yb;
	xb = rect->x2 - p->x; 
	yb = rect->y2 - p->y;
	float s4 = (xa * yb - ya * xb);
	float c4 = (xa * xb + ya * yb);

	float theta = atan2(s1, c1) + atan2(s2, c2) + atan2(s3, c3) + atan2(s4, c4);

#ifdef DEBUG
	printf(" yields theta = %.3f.", theta);
	if(theta > 6.25) printf(" returns T\n");
	else printf(" returns F\n");
#endif

	return theta > 6.25; 
}
#endif

Rectangle *group_rectangles(Rectangle *rects, int n, float beta, int *size, Rectangle *result) {
	int i, j;
	ExtendedRectangle *extended_rectangles = new ExtendedRectangle [ n ]; /* allocate maximum */
	if(result == 0) result = new Rectangle [ n ]; /* allocate maximum */
	for(i=0;i<n;++i) {
		Rectangle *rect = &rects[i];
		extended_rectangles[i].rect = rect;
		float a = area(rect);
		extended_rectangles[i].area = a;
		extended_rectangles[i].intersection_threshold = a * beta; 
		extended_rectangles[i].id = -1; /* not yet considered */
		extended_rectangles[i].prev = extended_rectangles[i].next = &extended_rectangles[i]; /* points to self */
	}

	for(i=0;i<n;++i) {
		ExtendedRectangle *C = &extended_rectangles[i];
		float a1 = C->area;
		float t1 = C->intersection_threshold; /* first threshold for intersection */
#ifdef DEBUG
printf("rectangle %d = %s\n", i, print_rectangle(recti->rect)); 
#endif
		for(j=i+1;j<n;++j) {
			ExtendedRectangle *D = &extended_rectangles[j];

			if(D->prev != D || D->next != D) continue; /* already processed */

			float t2 = D->intersection_threshold; /* 2nd threshold for intersection */
			float a = intersection(C->rect, D->rect);
			if((a > t1) || (a > t2)) {
#ifdef DEBUG
printf("rectangle %d merges with %d\n", i, j);
#endif
				ExtendedRectangle *A = C->next;
				ExtendedRectangle *F = D->prev;

				C->next = D;
				D->prev = C;
				A->prev = F;
				F->next = A;
				
			}
		}
	}

	int index = 0;
	for(i=0;i<n;++i) {
		ExtendedRectangle *rect0 = &extended_rectangles[i], *rect = rect0;
		if(rect->id == 0) continue; /* already been processed */
		rect->id = 0;
		float a = rect->area, atot = a;
		float xmin = a * rect->rect->x1;
		float xmax = a * rect->rect->x2;
		float ymin = a * rect->rect->y1;
		float ymax = a * rect->rect->y2;
#ifdef DEBUG
printf("A: summing rectangle: %s\n", print_rectangle(rect->rect));
#endif
		while(rect->next != rect0) {
			rect = rect->next;
			rect->id = 0;
#ifdef DEBUG
printf("B: summing rectangle: %s\n", print_rectangle(rect->rect));
#endif
			a = rect->area;
			xmin += a * rect->rect->x1;
			xmax += a * rect->rect->x2;
			ymin += a * rect->rect->y1;
			ymax += a * rect->rect->y2;
			atot += a;
		}
		xmin /= atot;
		xmax /= atot;
		ymin /= atot;
		ymax /= atot;
		result[index++] = { xmin, ymin, xmax, ymax };
	}

	*size = index;
	
	delete [] extended_rectangles;

	return result;
}

