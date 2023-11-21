#pragma once
#include "Vec3.h"

class Ray
{
public:
	Ray() = default;
	Ray(const vec3& origin, const vec3& direction);
	vec3 At(double t) const;

	vec3 At(double t);
public:
	vec3 orig;
	vec3 dir;
};

inline Ray::Ray(const vec3& origin, const vec3& direction) :orig(origin), dir(direction)
{
}

inline vec3 Ray::At(double t) const
{
	return orig + t * dir;
}
