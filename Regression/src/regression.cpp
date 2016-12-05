#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float cost(float *x, float *y, int n, float m, float b) {
}

float regression(float *x, float *y, int n, float *slope, float *intercept, int option) {
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
	float m, b;
	if (option == 0) {
// printf("sxy = %f. sxx = %f\n", sxy, sxx);
		m = sxy / sxx;
	} else {
		float syy = muyy - mux * muy;
		m = tan(0.5 * atan2(sxy, sxx - syy));
	}
	b = muy - m * mux; 

	*slope = m;
	*intercept = b;

/* calculate the cost function */
	float S = 0.0f;
	for(int i=0;i<n;++i) {
		S += fabs(m * x[i] - y[i] + b);
	}
	S = S / sqrt(1.0f + m * m);
	return S;
}

#ifdef TEST

#define N 10
float x[N], y[N];

int main(int argc, char **argv) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> dist(1.0, 0.05);

	float m, b, S;

	/* no errors on x. only equal errors on y */
	for(int i=0;i<N;++i) {
		float abscissa = i;
		x[i] = i; 
		y[i] = i + dist(gen) - 1.0f;
		printf("random value %d = (%f, %f)\n", i, x[i], y[i]);
	}

	S = regression(x, y, N, &m, &b, 0);
	printf("linear regression gives y = %.3f x + %.3f. S = %f\n", m, b, S);
	S = regression(x, y, N, &m, &b, 1);
	printf("normal regression gives y = %.3f x + %.3f. S = %f\n", m, b, S);

	/* equal errors on x, y */
	for(int i=0;i<N;++i) {
		float abscissa = i;
		x[i] = i + dist(gen) - 1.0f; 
		// y[i] = i + dist(gen) - 1.0f;
		printf("random value %d = (%f, %f)\n", i, x[i], y[i]);
	}

	S = regression(x, y, N, &m, &b, 0);
	printf("linear regression gives y = %.3f x + %.3f. S = %f\n", m, b, S);
	S = regression(x, y, N, &m, &b, 1);
	printf("normal regression gives y = %.3f x + %.3f. S = %f\n", m, b, S);

}

#endif
