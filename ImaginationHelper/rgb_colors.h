#pragma once
#include <stdint.h>
///////////////////////////////////////////////////
// Struct RGB with uint8_t

struct RGB_i;
struct RGB_d;

struct RGB_i8 {
	RGB_i8() : r(0), g(0), b(0) {};
	RGB_i8(const RGB_i & tmp);
	RGB_i8(const RGB_d & tmp);
	RGB_i operator+(const RGB_i8 & t) const;

	uint8_t r;
	uint8_t g;
	uint8_t b;
};

////////////////////////////////////////////////////
// Struct RGB with int

struct RGB_i {
	RGB_i() : r(0), g(0), b(0) {};
	RGB_i(const RGB_i8 & tmp) : r(tmp.r), g(tmp.g), b(tmp.b) {};

	RGB_i operator*(const double & t) const {
		RGB_i result;
		result.r = r * t;
		result.g = g * t;
		result.b = b * t;

		return result;
	}

	RGB_i8 operator/(const double & t) const {
		RGB_i8 result;
		result.r = r / t;
		result.g = g / t;
		result.b = b / t;

		return result;
	}

	RGB_i operator+(const RGB_i8 & t) const {
		RGB_i result;
		result.r = r + t.r;
		result.g = g + t.g;
		result.b = b + t.b;

		return result;
	}

	RGB_i operator+(const RGB_i & t) const {
		RGB_i result;
		result.r = r + t.r;
		result.g = g + t.g;
		result.b = b + t.b;

		return result;
	}

	RGB_i operator+=(const RGB_i8 & t) {
		*this = *this + t;
		return *this;
	}

	RGB_i operator+=(const RGB_i & t) {
		*this = *this + t;
		return *this;
	}

	int r;
	int g;
	int b;
};

/////////////////////////////////////////////////////
// Struct RGB with double

struct RGB_d {
	RGB_d() : r(0), g(0), b(0) {};
	RGB_d(const RGB_i & tmp) : r(tmp.r), g(tmp.g), b(tmp.b) {};

	RGB_d operator/ (const float & a) const {
		RGB_d result;
		result.r = r / a;
		result.g = g / a;
		result.b = b / a;

		return result;
	}

	RGB_d operator* (const float & a) const {
		RGB_d result;
		result.r = r * a;
		result.g = g * a;
		result.b = b * a;

		return result;
	}

	RGB_d operator* (const RGB_d & a) const {
		RGB_d result;
		result.r = r * a.r;
		result.g = g * a.g;
		result.b = b * a.b;

		return result;
	}

	RGB_d operator+ (const RGB_d & a) const {
		RGB_d result;
		result.r = r + a.r;
		result.g = g + a.g;
		result.b = b + a.b;

		return result;
	}

	RGB_d operator+= (const RGB_d & a) {
		*this = *this + a;
		return *this;
	}

	double r;
	double g;
	double b;
};