#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "group_rectangles.h"

using namespace cv;
using namespace std;

Rectangle rectangles[] = {
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

	{ -1.0,  0.0,  0.0,  0.0 }
};

float scale = 0.0;

int main(int argc, char **argv) {
	int i, size, nrects = 0;
	for(nrects=0;rectangles[nrects].x1>=0;) ++nrects; /* count the rectangles */
	for(i=0;i<nrects;++i) if(rectangles[i].y2 > scale) scale = rectangles[i].y2;
	printf("found %d rectangles as input. scale = %.1f\n", nrects, scale);
	Rectangle *new_rectangles = group_rectangles(rectangles, nrects, 0.1, &size);
	printf("%d old rectangles\n", nrects);
	for(i=0;i<nrects;++i) printf("%s\n", print_rectangle(&rectangles[i]));
	printf("%d new rectangles\n", size);
	for(i=0;i<size;++i) printf("%s\n", print_rectangle(&new_rectangles[i]));

	int w = 350, h = 250;
	Mat frame = Mat::zeros(h, w, CV_8UC3);

	Scalar old_color = Scalar(0xff, 0x00, 0x00);
	Scalar new_color = Scalar(0x00, 0x00, 0xff);

	for(i=0;i<size;++i) {
		float x = w * new_rectangles[i].x1 / scale; 
		float y = h * new_rectangles[i].y1 / scale; 
		float dx = w * (new_rectangles[i].x2 - new_rectangles[i].x1) / scale; 
		float dy = h * (new_rectangles[i].y2 - new_rectangles[i].y1) / scale; 
		Rect rect(x, y, dx, dy);
		cv::rectangle(frame, rect, new_color, 3);
	}

	for(i=0;i<nrects;++i) {
		float x = w * rectangles[i].x1 / scale; 
		float y = h * rectangles[i].y1 / scale; 
		float dx = w * (rectangles[i].x2 - rectangles[i].x1) / scale; 
		float dy = h * (rectangles[i].y2 - rectangles[i].y1) / scale; 
		Rect rect(x, y, dx, dy);
		cv::rectangle(frame, rect, old_color, 1);
	}

	namedWindow("main", 1);
	imshow("main", frame);
	int ch = waitKey(0);

	delete [] new_rectangles;

	// C++: void rectangle(Mat& img, Rect rec, const Scalar& color, int thickness=1, int lineType=8, int shift=0);

	return 0;
}
