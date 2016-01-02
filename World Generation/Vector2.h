#ifndef _VECTOR2_H
#define _VECTOR2_H

#include <math.h>

class Vector2 {

public:

	// vars
	float x, y;

	// constructors
	Vector2() {}

	Vector2(float x1, float y1) {

		x = x1; y = y1;;

	}

	// vector ops
	void Normalize() {

		float fTemp = 1 / Length();

		x *= fTemp;
		y *= fTemp;

	}

	inline double Length() const {

		return(sqrt((x * x) + (y * y)));

	}

	//  operators
	Vector2 operator + (const Vector2 & rhs) const {

		return(Vector2(x + rhs.x, y + rhs.y));

	}

	Vector2 operator - (const Vector2 & rhs) const {

		return(Vector2(x - rhs.x, y - rhs.y));

	}

	Vector2 operator / (float k) const {

		return(Vector2(x / k, y / k));

	}

	float operator * (const Vector2 & rhs) const {

		// dot product
		return((x * rhs.x) + (y * rhs.y));

	}

	float & operator [] (int n) {

		// access like an array
		switch (n) {

		case 0: return(x);
		case 1: return(y);
		default: /* bug out */;

		}
	}

}; // end class
#endif