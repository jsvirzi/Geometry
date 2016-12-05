#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float cost(float *x, float *y, int n, float m, float b, int option) {
	float S = 0.0f;
	for(int i=0;i<n;++i) {
		S += fabs(m * x[i] - y[i] + b);
	}
	if(option == 1) {
		S = S / sqrt(1.0f + m * m);
	}
	return S;
}

/* minimal code between here */

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
	if(option == 0) {
		m = sxy / sxx;
	} else {
		float syy = muyy - muy * muy;
		float txy = syy - sxx;
		m = (txy + sqrt(txy * txy + 4.0f * sxy * sxy)) / (2.0f * sxy); 
	}
	b = muy - m * mux; 

	*slope = m;
	*intercept = b;

	return -1.0f; /* TODO return the regression measure */
	/* uncomment the following line instead to return the cost function */
	/* return cost(x, y, n, m, b, option); */
}

/* and here */

#ifdef TEST

#define N 10
float x[N], y[N];

int main(int argc, char **argv) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> dist(1.0, 0.05);

	float m, b, S;
	float mTrue = 1.0, bTrue = 0.0, T;

	/* no errors on x. only equal errors on y */
	for(int i=0;i<N;++i) {
		float abscissa = i;
		x[i] = i; 
		y[i] = mTrue * i + dist(gen) - 1.0f;
		printf("random value %d = (%f, %f)\n", i, x[i], y[i]);
	}

	S = regression(x, y, N, &m, &b, 0);
	T = cost(x, y, N, mTrue, bTrue, 0);
	printf("linear regression gives y = %.3f x + %.3f. S = %f. T = %f\n", m, b, S, T);
	S = regression(x, y, N, &m, &b, 1);
	T = cost(x, y, N, mTrue, bTrue, 1);
	printf("normal regression gives y = %.3f x + %.3f. S = %f. T = %f\n", m, b, S, T);

	/* equal errors on x, y */
	for(int i=0;i<N;++i) {
		float abscissa = i;
		x[i] = i + dist(gen) - 1.0f; 
		printf("random value %d = (%f, %f)\n", i, x[i], y[i]);
	}

	S = regression(x, y, N, &m, &b, 0);
	T = cost(x, y, N, mTrue, bTrue, 0);
	printf("linear regression gives y = %.3f x + %.3f. S = %f. T = %f\n", m, b, S, T);
	S = regression(x, y, N, &m, &b, 1);
	T = cost(x, y, N, mTrue, bTrue, 1);
	printf("normal regression gives y = %.3f x + %.3f. S = %f. T = %f\n", m, b, S, T);

	return 0;
}

#endif
