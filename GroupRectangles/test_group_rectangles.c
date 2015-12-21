#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "group_rectangles.h"

using namespace cv;
using namespace std;

Rectangle rectangles[] = {

	{ 1.0, 1.0, 4.0, 4.0 },
	{ 1.5, 1.5, 4.5, 4.5 },
	{ 2.0, 2.0, 5.0, 5.0 },

	// { 21.0, 21.0, 24.0, 24.0 },
	// { 21.5, 21.5, 24.5, 24.5 },
	// { 22.0, 22.0, 25.0, 25.0 },

	{ -1.0,  0.0,  0.0,  0.0 },

	// {  0.0,  0.0,  2.0,  2.0 },
	// {  1.0,  1.0,  3.0,  3.0 },
	// {  4.0,  4.0,  5.0,  5.0 },
	// {  2.0,  0.0,  4.0,  2.0 },
	// {  2.0,  4.0,  8.0,  6.0 },
	// {  4.0,  4.0,  6.0,  5.0 },

	{  1.0,  9.0,  7.0, 11.0 },
	{  3.0,  9.0,  5.0, 11.0 },
	// // {  5.0,  9.0,  5.0, 11.0 },
	// // {  7.0,  9.0,  7.0, 11.0 },

	// {  9.0,  9.0, 15.0, 15.0 }, 
	// { 11.0,  8.0, 13.0, 13.0 },

	{  1.0,  1.0,  4.0,  4.0 },
	{  2.0,  3.0,  3.0,  4.0 },

	{  5.0,  1.0,  8.0,  4.0 },
	{  7.0,  2.0,  8.0,  3.0 },

	{  9.0,  1.0, 12.0,  4.0 },
	{ 10.0,  1.0, 11.0,  2.0 },

	{  1.0,  5.0,  4.0,  8.0 },
	{  1.0,  6.0,  2.0,  7.0 },

	{  5.0,  5.0,  7.0,  8.0 },
	{  6.0,  5.0,  8.0,  8.0 },

	{  9.0,  5.0, 12.0,  8.0 },
	{ 10.0,  5.0, 11.0,  8.0 },

	{  1.0,  9.0,  4.0, 12.0 },
	{  1.0,  9.0,  2.0, 10.0 },

	{  5.0,  9.0,  8.0, 12.0 },
	{  7.0,  9.0,  8.0, 10.0 },

	{  9.0,  9.0, 12.0, 12.0 },
	{ 11.0, 11.0, 12.0, 12.0 },

	{  1.0, 13.0,  4.0, 16.0 },
	{  1.0, 15.0,  2.0, 16.0 },

	{ -1.0,  0.0,  0.0,  0.0 }
};

float xscale = 0.0, yscale = 0.0;

#define MAX_RECTANGLES 1000
Rectangle new_rectangles [ MAX_RECTANGLES ];

int main(int argc, char **argv) {
	int i, size, nrects = 0;
	for(nrects=0;rectangles[nrects].x1>=0;) ++nrects; /* count the rectangles */
	for(i=0;i<nrects;++i) if(rectangles[i].y2 > yscale) yscale = rectangles[i].y2;
	for(i=0;i<nrects;++i) if(rectangles[i].x2 > xscale) xscale = rectangles[i].x2;
	printf("found %d rectangles as input. scales = %.1f, %.1f\n", nrects, xscale, yscale);
	xscale = 1.1 * xscale;
	yscale = 1.1 * yscale;
	size = MAX_RECTANGLES;
	group_rectangles(rectangles, nrects, 0.1, &size, new_rectangles);
	printf("%d old rectangles\n", nrects);
	for(i=0;i<nrects;++i) printf("%s\n", print_rectangle(&rectangles[i]));
	printf("%d new rectangles\n", size);
	for(i=0;i<size;++i) printf("%s\n", print_rectangle(&new_rectangles[i]));

	int w = 350, h = 250;
	Mat frame = Mat::zeros(h, w, CV_8UC3);

	Scalar old_color[2] = { Scalar(0xff, 0x00, 0x00), Scalar(0x00, 0xff, 0x00) };
	Scalar new_color = Scalar(0x00, 0x00, 0xff);

	for(i=0;i<size;++i) {
		float x = w * new_rectangles[i].x1 / xscale; 
		float y = h * new_rectangles[i].y1 / yscale; 
		float dx = w * (new_rectangles[i].x2 - new_rectangles[i].x1) / xscale; 
		float dy = h * (new_rectangles[i].y2 - new_rectangles[i].y1) / yscale; 
		Rect rect(x, y, dx, dy);
		cv::rectangle(frame, rect, new_color, 3);
	}

	for(i=0;i<nrects;++i) {
		int index = i % 2;
		float x = w * rectangles[i].x1 / xscale; 
		float y = h * rectangles[i].y1 / yscale; 
		float dx = w * (rectangles[i].x2 - rectangles[i].x1) / xscale; 
		float dy = h * (rectangles[i].y2 - rectangles[i].y1) / yscale; 
		Rect rect(x, y, dx, dy);
		cv::rectangle(frame, rect, old_color[index], 1 + index);
	}

	namedWindow("main", 1);
	imshow("main", frame);
	int ch = waitKey(0);

	// C++: void rectangle(Mat& img, Rect rec, const Scalar& color, int thickness=1, int lineType=8, int shift=0);

	return 0;
}
