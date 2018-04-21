#pragma once
// Introduced in chapter 5
#include "ray.h"

class hitRecord
{
public:
	float t;
	vec3 p;
	vec3 n;
};

class hitable
{
public:
	virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& hitrec) const = 0;
};