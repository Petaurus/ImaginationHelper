#include "rgb_colors.h"

////////////////////////////////////////////////////////
// Declaration of forward declared functions

RGB_i8::RGB_i8(const RGB_i & tmp) : r(tmp.r), g(tmp.g), b(tmp.b) {};
RGB_i8::RGB_i8(const RGB_d & tmp) : r(tmp.r + .5), g(tmp.g + .5), b(tmp.b + .5) {};

RGB_i RGB_i8::operator+(const RGB_i8 & t) const {
	RGB_i result;
	result.r = r + t.r;
	result.g = g + t.g;
	result.b = b + t.b;

	return result;
}