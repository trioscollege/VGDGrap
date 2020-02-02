#pragma once
#include <iostream>

struct Vector3
{
public:
	float x, y, z;
	Vector3() : x(0), y(0), z(0) {}
	Vector3(float xx) : x(xx), y(xx), z(xx) {}
	Vector3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

	Vector3& Normalize() {
		float nor2 = Length2();
		if (nor2 > 0) {
			float invNor = 1 / sqrt(nor2);
			x *= invNor, y *= invNor, z *= invNor;
		}
		return *this;
	}

	Vector3 operator * (const float& f) const {
		return Vector3(x * f, y * f, z * f); 
	}

	Vector3 operator * (const Vector3&  v) const { 
		return Vector3(x * v.x, y * v.y, z * v.z); 
	}

	float Dot(const Vector3&  v) const { 
		return x * v.x + y * v.y + z * v.z; 
	}

	Vector3 operator - (const Vector3&  v) const { 
		return Vector3(x - v.x, y - v.y, z - v.z); 
	}

	Vector3 operator + (const Vector3&  v) const { 
		return Vector3(x + v.x, y + v.y, z + v.z); 
	}

	Vector3&  operator += (const Vector3&  v) { 
		x += v.x, y += v.y, z += v.z; return *this; 
	}

	Vector3&  operator *= (const Vector3&  v) { 
		x *= v.x, y *= v.y, z *= v.z; return *this; 
	}

	Vector3 operator - () const { 
		return Vector3(-x, -y, -z); 
	}

	float Length2() const { 
		return x * x + y * y + z * z; 
	}

	float Length() const { 
		return sqrt(Length2()); 
	}

	friend std::ostream& operator << (std::ostream& os, const Vector3&  v) {
		os << "[" << v.x << " " << v.y << " " << v.z << "]";
		return os;
	}

};