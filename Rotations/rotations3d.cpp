#include <math.h>

double *rotationMatrix(double n[3], double theta, double *matrix) {
	if(matrix == 0) matrix = new double[3 * 3];
	double c = cos(theta), s = sin(theta), a = (1.0 - c);
	double nx = n[0], ny = n[1], nz = n[2];
	matrix[3 * 0 + 0] = nx * nx * a + c; 
	matrix[3 * 0 + 1] = nx * ny * a - nz * s; 
	matrix[3 * 0 + 2] = nx * nz * a + ny * s;
	matrix[3 * 1 + 0] = ny * nx * a + nz * s;
	matrix[3 * 1 + 1] = ny * ny * a + c; 
	matrix[3 * 1 + 2] = ny * nz * a - nx * s; 
	matrix[3 * 2 + 0] = nz * nx * a - ny * s; 
	matrix[3 * 2 + 1] = nz * ny * a + nx * s; 
	matrix[3 * 2 + 2] = nz * nz * a + c; 
	return matrix;
}

double *unitCrossProduct(double a[3], double b[3], double *n) {
	if(n == 0) n = new double[3];
	n[0] = a[1] * b[2] - a[2] * b[1];
	n[1] = a[2] * b[0] - a[0] * b[2];
	n[2] = a[0] * b[1] - a[1] * b[0];
	double mag = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
	n[0] /= mag;
	n[1] /= mag;
	n[2] /= mag;
	return n;
}

double dotProduct(double a[3], double b[3]) {
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

double *rotateVector(double *R, double *a, double *b) {
	if(b == 0) b = new double[3];
	for(int i=0;i<3;++i) {
		b[i] = 0.0;
		for(int j=0;j<3;++j) {
			b[i] += R[3 * i + j] * a[j]; 
		}
	}
	return b;
}

#ifdef TEST

#include <stdio.h>

int main(int argc, char **argv) {
	double a[3], n[3], u[3], R[3 * 3], g[3], theta = 51.0 * M_PI / 180.0;
	g[0] = 0.0; g[1] = 0.0; g[2] = 1.0;
	a[0] = sin(theta); a[1] = 0.0; a[2] = - cos(theta); 
	unitCrossProduct(a, g, n);
	rotationMatrix(n, theta, R);
	rotateVector(R, n, u);
	printf("Rn = (%.3f, %.3f, %.3f) n = (%.3f, %.3f, %.3f)\n", u[0], u[1], u[2], n[0], n[1], n[2]); 
	printf("cos(theta) = %.3f. compare to %.3f\n", cos(theta), -dotProduct(a, g));
}

#endif
