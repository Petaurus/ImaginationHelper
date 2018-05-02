#pragma once
#include "rgb_colors.h"
#include "vec2.h"

#define INV_SQRT_2PI_BY_3 1.1968268412042981641
double inv_sqrt_value = 0;
double exp_value = 0;

// Calculate average color
void average(RGB_i8 * base, const RGB_i8 * sourse) {
	for (int i = 0; i < HEIGHT * WIDTH; i++) {
		*(base + i) = ((RGB_i)*(base + i) + *(sourse + i)) / 2;
	}
}

// Multiplication of colors
void multiplication(RGB_i8 * base, const RGB_i8 * sourse) {
	for (int i = 0; i < HEIGHT * WIDTH; i++) {
		RGB_d n1 = (RGB_d)(*(base + i)) / 255;
		RGB_d n2 = (RGB_d)(*(sourse + i)) / 255;
		*(base + i) = (n1 * n2) * 255;
	}
}

RGB_d operator- (const double & left, const RGB_d & right) {
	RGB_d result;
	result.r = left - right.r;
	result.g = left - right.g;
	result.b = left - right.b;

	return result;
}

// Multiplication of inverted colors
void lighting(RGB_i8 * base, const RGB_i8 * sourse) {
	for (int i = 0; i < HEIGHT * WIDTH; i++) {
		RGB_d n1 = 1 - (RGB_d)(*(base + i)) / 255;
		RGB_d n2 = 1 - (RGB_d)(*(sourse + i)) / 255;
		*(base + i) = (n1 * n2) * 255;
	}
}

const RGB_i8 & getPixel(const RGB_i8 * sourse, Vec2<int> pos) {
	pos.x = (pos.x + WIDTH) % WIDTH;
	pos.y = (pos.y + HEIGHT) % HEIGHT;
	return *(sourse + pos.x + pos.y * WIDTH);
}

// Smoothing using the triangle distribution
RGB_i8 old_blur(const RGB_i8 * sourse, Vec2<int> pos, int radius, Vec2<int> step) {

	int totalScale = (radius + 1);
	RGB_i result = (RGB_i)(getPixel(sourse, pos)) * totalScale;
	Vec2<int> c_step;
	int i = 1;
	while (i <= radius) {
		int scale = totalScale - i;
		c_step = step * i;
		result += (getPixel(sourse, pos + c_step) + getPixel(sourse, pos - c_step)) * scale;

		i++;
	}

	return result / (totalScale * totalScale);
}

// Smoothing using the normal distribution
RGB_i8 blur(const RGB_i8 * sourse, Vec2<int> pos, int radius, Vec2<int> step) {
	RGB_d result;
	double sum = 0;
	Vec2<int> c_step;

	int i = 1;
	while (i <= radius) {
		double scale = inv_sqrt_value * exp(exp_value * i * i);
		sum += 2. * scale;
		c_step = step * i;
		result = result + (RGB_d)(getPixel(sourse, pos + c_step) + getPixel(sourse, pos - c_step)) * scale;

		i++;
	}

	result += (RGB_d)getPixel(sourse, pos) * (1 - sum);
	return result;
}

void smoothingImage(RGB_i8 * image, int radius = 10, int pow = 1) {

	inv_sqrt_value = INV_SQRT_2PI_BY_3 / radius;
	exp_value = -4.5 / (radius * radius);

	auto blur_func = [](RGB_i8 * image, int radius, Vec2<int> step) {

		RGB_i8 * result = new RGB_i8[HEIGHT * WIDTH];

		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < WIDTH; x++) {
				RGB_i8 pxl = blur(image, Vec2<int>(x, y), radius, step);

				int pos = (x + y * WIDTH);
				*(result + pos) = pxl;
			}
		}
		for (int i = 0; i < HEIGHT * WIDTH; i++) {
			*(image + i) = *(result + i);
		}

		delete[] result;
	};

	for (int i = 0; i < pow; i++) {
		blur_func(image, radius, Vec2<int>(1, 0));
		blur_func(image, radius, Vec2<int>(0, 1));
	}
}