
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	double re;
	double im;
} Complex;

Complex complex_from_parts(double re, double im) {
	Complex complex;
	complex.re = re;
	complex.im = im;
	return complex;
}

double modulus(Complex z) {
	return sqrt(z.re * z.re + z.im * z.im);
}

Complex multiply(Complex x, Complex y) {
	return complex_from_parts(x.re * y.re - x.im * y.im, x.re * y.im + x.im * y.re);
}

Complex add(Complex x, Complex y) {
	return complex_from_parts(x.re + y.re, x.im + y.im);
}

double lerp(double a, double b, double t) {
	return a + (b - a) * t;
}

double count_iterations(double x_0, double y_0, int max_iter) {
	double radius = 2;
	Complex c = complex_from_parts(-0.8, 0.156);
	Complex z_n = complex_from_parts(x_0, y_0);
	int i = 0;

	while (modulus(z_n) < radius * radius && i < max_iter) {
		z_n = add(multiply(z_n, z_n), c);
		i++;
	}
	
	return i;
}

double average_for_px(int x, int y, int max_x, int max_y, int max_iter) {
	int samples = 16;
	double avg_iter = 0;
	double radius = 2;

	int n = samples;

	while (n--) {
		double x_offs = (double)rand()/(double)(RAND_MAX);
		double y_offs = (double)rand()/(double)(RAND_MAX);
		double x_0 = x + x_offs;
		double y_0 = y + y_offs;
		x_0 = lerp(-radius, radius, x_0 / (double) max_x);
		y_0 = lerp(-radius, radius, y_0 / (double) max_y);
		avg_iter += count_iterations(x_0, y_0, max_iter) / (double) (samples);
	}

	return avg_iter / (double) max_iter;
}

int main() {
	srand(time(NULL));
	int width = 6000;
	int height = 6000;
	printf("P3\n%d\n%d\n255\n", width, height);
	
	for (int j = height - 1; j >= 0; j--) {
		for (int i = 0; i < width; i++) {
			double px = average_for_px(i, j, width, height, 700);
			int l = (int) lerp(0, 255, px);
			printf("%d %d %d\n", l, l, l);
		}
	}

	return 0;
}


