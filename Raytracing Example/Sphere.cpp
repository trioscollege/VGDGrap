#include "Sphere.h"

Sphere::Sphere(const Vector3& c, const float& r, const Vector3& sc, const float& refl, const float& transp, const Vector3& ec)
	: center(c), radius(r), radius2(r* r), surfaceColor(sc), emissionColor(ec), transparency(transp), reflection(refl)
{
}

bool Sphere::Intersect(const Vector3& origin, const Vector3& direction, float& p1, float& p2) const
{
	Vector3 len = center - origin;
	float tca = len.Dot(direction);
	if (tca < 0) return false;
	float d2 = len.Dot(len) - tca * tca;
	if (d2 > radius2) return false;
	float thc = sqrt(radius2 - d2);
	p1 = tca - thc;
	p2 = tca + thc;

	return true;
}
