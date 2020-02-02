#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>

#include "RayTracer.h"
#include "MathHelper.h"
#include "Sphere.h"

#define M_PI 3.141592653589793
#define MAX_RAY_DEPTH 5


float RayTracer::Mix(const float& x, const float& y, const float& mix)
{
	return y * mix + x * (1 - mix);

}

Vector3 RayTracer::Trace(const Vector3& origin, const Vector3& direction, const std::vector<Sphere>& spheres, const int& depth)
{
	//if (raydir.length() != 1) std::cerr << "Error " << raydir << std::endl;
	float tnear = INFINITY;
	const Sphere* sphere = NULL;
	// find intersection of this ray with the sphere in the scene
	for (unsigned i = 0; i < spheres.size(); ++i) {
		float p1 = INFINITY, p2 = INFINITY;
		if (spheres[i].Intersect(origin, direction, p1, p2)) {
			if (p1 < 0) p1 = p2;
			if (p1 < tnear) {
				tnear = p1;
				sphere = &spheres[i];
			}
		}
	}
	// if there's no intersection return black or background color
	if (!sphere) return Vector3(2);
    Vector3 surfaceColor = 0; // color of the ray/surfaceof the object intersected by the ray
    Vector3 phit = origin + direction * tnear; // point of intersection
    Vector3 nhit = phit - sphere->center; // normal at the intersection point
	nhit.Normalize(); // normalize normal direction
	// If the normal and the view direction are not opposite to each other
	// reverse the normal direction. That also means we are inside the sphere so set
	// the inside bool to true. Finally reverse the sign of IdotN which we want
	// positive.
	float bias = 1e-4; // add some bias to the point from which we will be tracing
	bool inside = false;
	if (direction.Dot(nhit) > 0) nhit = -nhit, inside = true;
	if ((sphere->transparency > 0 || sphere->reflection > 0) && depth < MAX_RAY_DEPTH) {
		float facingratio = -direction.Dot(nhit);
		// change the mix value to tweak the effect
		float fresneleffect = Mix(pow(1 - facingratio, 3), 1, 0.1);
		// compute reflection direction (not need to normalize because all vectors
		// are already normalized)
		Vector3 refldir = direction - nhit * 2 * direction.Dot(nhit);
		refldir.Normalize();
        Vector3 reflection = Trace(phit + nhit * bias, refldir, spheres, depth + 1);
        Vector3 refraction = 0;
		// if the sphere is also transparent compute refraction ray (transmission)
		if (sphere->transparency) {
			float ior = 1.1, eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface?
			float cosi = -nhit.Dot(direction);
			float k = 1 - eta * eta * (1 - cosi * cosi);
            Vector3 refrdir = direction * eta + nhit * (eta * cosi - sqrt(k));
			refrdir.Normalize();
			refraction = Trace(phit - nhit * bias, refrdir, spheres, depth + 1);
		}
		// the result is a mix of reflection and refraction (if the sphere is transparent)
		surfaceColor = (
			reflection * fresneleffect +
			refraction * (1 - fresneleffect) * sphere->transparency) * sphere->surfaceColor;
	}
	else {
		// it's a diffuse object, no need to ray trace any further
		for (unsigned i = 0; i < spheres.size(); ++i) {
			if (spheres[i].emissionColor.x > 0) {
				// this is a light
                Vector3 transmission = 1;
                Vector3 lightDirection = spheres[i].center - phit;
				lightDirection.Normalize();
				for (unsigned j = 0; j < spheres.size(); ++j) {
					if (i != j) {
						float p1, p2;
						if (spheres[j].Intersect(phit + nhit * bias, lightDirection, p1, p2)) {
							transmission = 0;
							break;
						}
					}
				}
				surfaceColor += sphere->surfaceColor * transmission *
					std::max(float(0), nhit.Dot(lightDirection)) * spheres[i].emissionColor;

			}
		}
	}

	return surfaceColor + sphere->emissionColor;
}

void RayTracer::Render(const std::vector<Sphere>& spheres)
{
	unsigned width = 1920, height = 1080;
    Vector3* image = new Vector3[width * height], * pixel = image;
	float invWidth = 1 / float(width), invHeight = 1 / float(height);
	float fov = 30, aspectratio = width / float(height);
	float angle = tan(M_PI * 0.5 * fov / 180.);
	// Trace rays
	for (unsigned y = 0; y < height; ++y) {
		for (unsigned x = 0; x < width; ++x, ++pixel) {
			float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
			float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
            Vector3 raydir(xx, yy, -1);
			raydir.Normalize();
			*pixel = Trace(Vector3(0), raydir, spheres, 0);
		}
	}
	// Save result to a PPM image (keep these flags if you compile under Windows)
	std::ofstream ofs("./untitled.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";
	for (unsigned i = 0; i < width * height; ++i) {
		ofs << (unsigned char)(std::min(float(1), image[i].x) * 255) <<
			(unsigned char)(std::min(float(1), image[i].y) * 255) <<
			(unsigned char)(std::min(float(1), image[i].z) * 255);
	}
	ofs.close();
	delete[] image;
}
