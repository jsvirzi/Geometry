#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int orthogonalRegression(float *x, float *y, int n, float *m, float *b, int option) {
	float mux = 0.0f, muy = 0.0f, muxx = 0.0f, muxy = 0.0f, muyy = 0.0f;
	for(int i=0;i<n;++i) {
		float tx = x[i];
		float ty = y[i];
		mux += tx;
		muy += ty;
		muxx += tx * tx;
		muxy += tx * ty;
		muyy += ty * ty;
	}
	mux /= n;
	muy /= n;
	muxx /= n;
	muxy /= n;
	muyy /= n;
	float sxx = muxx - mux * mux;
	float sxy = muxy - mux * muy;
	float syy = muyy - mux * muy;
	if (option == 0) {
		*m = atan2(sxy, sxx);
	} else {
		*m = tan(0.5 * atan2(sxy, sxx - syy));
	}
	*b = muy - (*m) * mux; 
	return 0;
}

#ifdef TEST

#define N 10
float x[N], y[N];

int main(int argc, char **argv) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> dist(1.0, 0.05);

	// unsigned int seed = 1234;
	// srandom(seed);
	for(int i=0;i<N;++i) {
		float abscissa = i;
		x[i] = dist(gen); 
		y[i] = i + dist(gen);
		// y[i] = (float)random();
		// y[i] /= RAND_MAX;
		printf("random value %d = (%f, %f)\n", i, x[i], y[i]);
	}
}

#endif
