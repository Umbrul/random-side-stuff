#ifndef _POINT_H
#define _POINT_H

#include <math.h>

class Point {

public:

	// vars
	float x, y, z;

	// constructors
	Point() {}

	Point(float x1, float y1, float z1) {

		x = x1; y = y1; z = z1;

	}

	// vector ops
	void Normalize() {

		float fTemp = 1 / Length();

		x *= fTemp;
		y *= fTemp;
		z *= fTemp;

	}

	inline double Length() const {

		return(sqrt((x * x) + (y * y) + (z * z)));

	}

	//  operators
	Point operator + (const Point & rhs) const {

		return(Point(x + rhs.x, y + rhs.y, z + rhs.z));

	}

	Point operator - (const Point & rhs) const {

		return(Point(x - rhs.x, y - rhs.y, z - rhs.z));

	}

	Point operator / (float k) const {

		return(Point(x / k, y / k, z / k));

	}

	float operator * (const Point & rhs) const {

		// dot product
		return((x * rhs.x) + (y * rhs.y) + (z * rhs.z));

	}

	float & operator [] (int n) {

		// access like an array
		switch (n) {

		case 0: return(x);
		case 1: return(y);
		case 2: return(z);
		default: /* bug out */;

		}
	}

}; // end class
#endif