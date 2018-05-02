#pragma once
/////////////////////////////////////////////////
// Include
#include <SFML\Graphics.hpp>

#define Vec2f Vec2<float> 

/////////////////////////////////////////////////
// Class Vec2
template <typename T>
class Vec2
{
public:
	Vec2() : x(0), y(0) {};
	Vec2(T X, T Y) : x(X), y(Y) {};
	Vec2(sf::Vector2f vec) : x(vec.x), y(vec.y) {};
	Vec2(sf::Vector2u vec) : x(vec.x), y(vec.y) {};

	template<typename u> Vec2(const Vec2<u> &a) : x(a.x), y(a.y) {};

	Vec2 operator+(const Vec2& a) const;
	Vec2 operator-(const Vec2& a) const;
	Vec2 operator+=(const Vec2& a);
	Vec2 operator*(const float& a) const;
	Vec2 operator*(const Vec2& a) const;
	Vec2 operator/(const float& a) const;
	Vec2 operator/(const Vec2& a) const;
	bool operator==(const Vec2& a) const;

	sf::Vector2f toSFVector() const;

	Vec2 normalized() const;
	Vec2 magnitude(float ragius) const;
	Vec2<int> toInt() const { return Vec2<int>((int)(x +.5f), (int)(y +.5f)); };
	float length() const;

	T x;
	T y;
};

template <typename T>
sf::Vector2f Vec2<T>::toSFVector() const {
	return sf::Vector2f(x, y);
}

template <typename T>
Vec2<T> Vec2<T>::normalized() const {
	float length = sqrtf(x*x + y * y);

	Vec2f tmp;
	if (length == 0)
		return tmp;

	tmp.x = x / length;
	tmp.y = y / length;

	return tmp;
}

template <typename T>
Vec2<T> Vec2<T>::magnitude(float radius) const {
	if (length() > radius) return normalized() * radius;
	else return *this;
}

template <typename T>
float Vec2<T>::length() const {
	return sqrtf(x*x + y * y);
}

template <typename T>
Vec2<T> Vec2<T>::operator+(const Vec2<T>& a) const {
	return Vec2<T>(x + a.x, y + a.y);
}

template <typename T>
Vec2<T> Vec2<T>::operator+=(const Vec2<T>& a) {
	return *this = *this + a;
}

template <typename T>
Vec2<T> Vec2<T>::operator*(const float& a) const {
	Vec2<T> tmp;
	tmp.x = x * a;
	tmp.y = y * a;
	return tmp;
}

template <typename T>
Vec2<T> Vec2<T>::operator*(const Vec2<T>& a) const {
	Vec2<T> tmp;
	tmp.x = x * a.x;
	tmp.y = y * a.y;
	return tmp;
}

template <typename T>
Vec2<T> Vec2<T>::operator/(const float& a) const {
	Vec2<T> tmp;
	tmp.x = x / a;
	tmp.y = y / a;
	return tmp;
}

template <typename T>
Vec2<T> Vec2<T>::operator/(const Vec2<T>& a) const {
	Vec2<T> tmp;
	tmp.x = x / a.x;
	tmp.y = y / a.y;
	return tmp;
}

template <typename T>
Vec2<T> Vec2<T>::operator-(const Vec2<T>& a) const {
	Vec2<T> tmp;
	tmp.x = x - a.x;
	tmp.y = y - a.y;
	return tmp;
}

template <typename T>
bool Vec2<T>::operator==(const Vec2<T>& a) const {
	if ((x == a.x) && (y == a.y)) return true;
	else return false;
}