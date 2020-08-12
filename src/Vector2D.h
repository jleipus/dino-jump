#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D {
private:
	float x;
	float y;

public:
	Vector2D(): x(0), y(0) 	{}
	Vector2D(float x, float y): x(x), y(y) {}

	float getX() { return x; }
	float getY() { return y; }

	void setX(float _x) { x = _x; }
	void setY(float _y) { y = _y; }

	float length();

	Vector2D operator + (const Vector2D& v2) const;
	friend Vector2D& operator += (Vector2D& v1, const Vector2D& v2);

	Vector2D operator * (float scalar);
	Vector2D& operator *= (float scalar);

	Vector2D operator - (const Vector2D& v2) const;
	friend Vector2D& operator -= (Vector2D& v1, const Vector2D& v2);

	Vector2D operator / (float scalar);
	Vector2D& operator /= (float scalar);

	//friend std::istream& operator>>(std::ostream& stream);
	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);

	void normalize();
};

#endif //VECTOR2D_H
