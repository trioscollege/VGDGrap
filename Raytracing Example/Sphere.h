#pragma once
#include "MathHelper.h"

class Sphere
{
public:
	float radius, radius2;
	float transparency, reflection;
	Vector3 center;
	Vector3 surfaceColor, emissionColor;

	Sphere(const Vector3& c, const float& r, const Vector3& sc, const float& refl = 0, const float& transp = 0, const Vector3& ec = 0);

	bool Intersect(const Vector3& origin, const Vector3& direction, float& p1, float& p2) const;

};