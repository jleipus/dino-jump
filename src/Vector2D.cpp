#include "Vector2D.h"
#include <math.h>

using namespace std;

float Vector2D::length() {
	return (float)sqrt((x * x) + (y * y));
}

Vector2D Vector2D::operator + (const Vector2D& v2) const {
	return Vector2D(x + v2.x, y + v2.y);
}

Vector2D& operator += (Vector2D& v1, const Vector2D& v2) {
	v1.x += v2.x;
	v1.y += v2.y;

	return v1;
}

Vector2D Vector2D::operator * (float scalar) {
	return Vector2D(x * scalar, y * scalar);
}

Vector2D& Vector2D::operator *= (float scalar) {
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2D Vector2D::operator - (const Vector2D& v2) const {
	return Vector2D(x - v2.x, y - v2.y);
}

Vector2D& operator -= (Vector2D& v1, const Vector2D& v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;

	return v1;
}

Vector2D Vector2D::operator / (float scalar) {
	return Vector2D(x / scalar, y / scalar);
}

Vector2D& Vector2D::operator /= (float scalar) {
	x /= scalar;
	y /= scalar;

	return *this;
}
/*
istream& operator>>(istream& stream) {

	float tmpX, tmpY;
	stream >> tmpX ;
	stream >> tmpY;

	cout << "(" << tmpX << "," << tmpY << ")";

	return stream;
}
*/
ostream& operator<<(ostream& stream, const Vector2D& vec) {
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}

void Vector2D::normalize() {
	float l = length();
	if(l > 0) {
		(*this) *= 1 / l;
	}
}
