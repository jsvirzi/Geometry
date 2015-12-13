#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct rectangle {
	float x1, y1, x2, y2;
} Rectangle; 

typedef struct line {
	float x1, y1, x2, y2;
} Line; 

typedef struct point {
	float x, y;
} Point;

float is_interior(Point *p, Rectangle *rect);

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

#if 0

float intersection(Rectangle *recta, Rectangle *rectb) {
	float ma, mb, ba, bb;
	ma = 0.0;
	if(recta->x1 != recta->recta->y1 - recta->y0; 
	float x1a = recta->x1, x2a = recta->x2;
	float x1b = rectb->x1, x2b = rectb->x2;
	bool overlap_x1a = (x1b <= x1a && x1a <= x2b);
	bool overlap_x2a = (x1b <= x2a && x2a <= x2b);
}

#endif

#if 0
merge_rectangles(float *alpha, Rectangle *irect, int n, float fraction) {
	Rectangle *rect;
	for(
}
#endif

bool intersect(Line *linea, Line *lineb, Point *p, bool intervals = true) {
	float x1a = linea->x1, x2a = linea->x2, y1a = linea->y1, y2a = linea->y2; 
	float x1b = lineb->x1, x2b = lineb->x2, y1b = lineb->y1, y2b = lineb->y2; 

	if(intervals) {

		float t;

	/* are the lines horizontal or vertical */
		bool linea_hor = false, linea_ver = false;
		if(x1a == x2a) { linea_ver = true; }
		else if(y1a == y2a) { linea_hor = true; }

		bool lineb_hor = false, lineb_ver = false;
		if(x1b == x2b) { lineb_ver = true; }
		else if(y1b == y2b) { lineb_hor = true; }

printf("hor ver = %s %s %s %s\n", linea_hor ? "true" : "false",  linea_ver ? "true" : "false",  lineb_hor ? "true" : "false",  lineb_ver ? "true" : "false");
#if 0
	/* order the intervals */
		if(x2a > x1a) { t = x2a; x2a = x1a; x1a = t; }
		if(y2a > y1a) { t = y2a; y2a = y1a; y1a = t; }
		if(x2b > x1b) { t = x2b; x2b = x1b; x1b = t; }
		if(y2b > y1b) { t = y2b; y2b = y1b; y1b = t; }
#endif

	/* if both lines are either horizontal or vertical, processing is straightforward */
		if(linea_hor && lineb_ver) {

		/* order the intervals */
			if(x2a < x1a) { t = x2a; x2a = x1a; x1a = t; }
			// if(y2a > y1a) { t = y2a; y2a = y1a; y1a = t; }
			// if(x2b > x1b) { t = x2b; x2b = x1b; x1b = t; }
			if(y2b < y1b) { t = y2b; y2b = y1b; y1b = t; }

printf("hello a x1a=%.1f x1b=%.1f x2b=%.1f x2a=%.1f\n", x1a, x1b, x2b, x2a);
printf("hello a y1b=%.1f y1a=%.1f y2a=%.1f y2b=%.1f\n", y1b, y1a, y2a, y2b);

			if((y1b < y1a && y2a < y2b) && (x1a < x1b && x2b < x2a)) {
				p->x = x1b;
				p->y = y1a;
				return true;
			}

		} else if(lineb_hor && linea_ver) {

		/* order the intervals */
			// if(x2a > x1a) { t = x2a; x2a = x1a; x1a = t; }
			if(y2a < y1a) { t = y2a; y2a = y1a; y1a = t; }
			if(x2b < x1b) { t = x2b; x2b = x1b; x1b = t; }
			// if(y2b > y1b) { t = y2b; y2b = y1b; y1b = t; }

printf("hello b x1b=%.1f x1a=%.1f x2a=%.1f x2b=%.1f\n", x1b, x1a, x2a, x2b);
printf("hello b y1a=%.1f y1b=%.1f y2b=%.1f y2a=%.1f\n", y1a, y1b, y2b, y2a);

			if((y1a < y1b && y2b < y2a) && (x1b < x1a && x2a < x2b)) {
				p->x = x1a;
				p->y = y1b;
				return true;
			}
		}
	} else {
	}
	return false;
}

/* assume ordered in x, y? */
float intersection(Rectangle *recta, Rectangle *rectb) {
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
	Point points[12];

	points[0] = { recta->x1, recta->y1 };
	points[1] = { recta->x1, recta->y2 };
	points[2] = { recta->x2, recta->y1 };
	points[3] = { recta->x2, recta->y2 };

	points[4] = { rectb->x1, rectb->y1 };
	points[5] = { rectb->x1, rectb->y2 };
	points[6] = { rectb->x2, rectb->y1 };
	points[7] = { rectb->x2, rectb->y2 };

	int index = 8;

	printf("A1\n"); if(intersect(&line1a, &line2c, &p)) { printf("intersection = (%.1f, %.1f)\n", p.x, p.y); points[index++] = p; };
	printf("A2\n"); if(intersect(&line1a, &line2d, &p)) { printf("intersection = (%.1f, %.1f)\n", p.x, p.y); points[index++] = p; };
	printf("B1\n"); if(intersect(&line1b, &line2c, &p)) { printf("intersection = (%.1f, %.1f)\n", p.x, p.y); points[index++] = p; };
	printf("B2\n"); if(intersect(&line1b, &line2d, &p)) { printf("intersection = (%.1f, %.1f)\n", p.x, p.y); points[index++] = p; };
	printf("C1\n"); if(intersect(&line1c, &line2a, &p)) { printf("intersection = (%.1f, %.1f)\n", p.x, p.y); points[index++] = p; };
	printf("C2\n"); if(intersect(&line1c, &line2b, &p)) { printf("intersection = (%.1f, %.1f)\n", p.x, p.y); points[index++] = p; };
	printf("D1\n"); if(intersect(&line1d, &line2a, &p)) { printf("intersection = (%.1f, %.1f)\n", p.x, p.y); points[index++] = p; };
	printf("D2\n"); if(intersect(&line1d, &line2b, &p)) { printf("intersection = (%.1f, %.1f)\n", p.x, p.y); points[index++] = p; };

	printf("%d points\n", index);

	int n = 0;
	Point pts[12];

	printf("uber rectangle = (%.1f, %.1f) x (%.1f, %.1f)\n", uber_rectangle.x1, uber_rectangle.y1, uber_rectangle.x2, uber_rectangle.y2);
	for(int i=0;i<index;++i) {
		float a = is_interior(&points[i], &uber_rectangle); 
		printf("point=(%.1f,%.1f) is %.1f\n", points[i].x, points[i].y, a);
		if(a > 0.95) {
			pts[n++] = points[i];
		}
	}

	if(n == 4) {
		printf("final area = %f\n", area(pts, n));

		p = pts[1];
		pts[1] = pts[2];
		pts[2] = p;

		p = pts[0];
		pts[0] = pts[1];
		pts[1] = pts[2];
		pts[2] = pts[3];
		pts[3] = p;
		printf("final area = %f\n", area(pts, n));
	}

#if 0
	Point p;
	p = { recta->x1, recta->y1 };
	printf("point1 interior = %f\n", is_interior(&p, &uber_rectangle);
	p = { recta->x1, recta->y2 };
	p = { recta->x2, recta->y1 };
	p = { recta->x2, recta->y2 };
#endif
}

/* y2 = y1, y4 = y3, x3 = x2, x4 = x1 */
float is_interior(Point *p, Rectangle *rect) {

	if(p->x == rect->x1) return 0.0;
	if(p->x == rect->x2) return 0.0;
	if(p->y == rect->y1) return 0.0;
	if(p->y == rect->y2) return 0.0;

	printf("is_interior: P=(%f,%f) R=(%f,%f)x(%f,%f)\n", p->x, p->y, rect->x1, rect->y1, rect->x2, rect->y2);

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

	return atan2(s1, c1) + atan2(s2, c2) + atan2(s3, c3) + atan2(s4, c4);
}

int main(int argc, char **argv) {
	Rectangle recta = { 0.0, 0.0, 2.0, 2.0 };
	Rectangle rectb = { 1.0, 1.0, 3.0, 3.0 };
	float x = atof(argv[1]);
	float y = atof(argv[2]);
	Point p = { x, y };
	float a = is_interior(&p, &recta);
	printf("A = %f\n", a);
	intersection(&recta, &rectb);
	return 0;
}
