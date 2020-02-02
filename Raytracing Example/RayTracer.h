#pragma once
#include <vector>

class Vector3;
class Sphere;

class RayTracer
{
public:
	float Mix(const float& x, const float& y, const float& mix);

	Vector3 Trace(const Vector3& origin, const Vector3& direction, const std::vector<Sphere>& spheres, const int& depth);
	void Render(const std::vector<Sphere>& spheres);

};
