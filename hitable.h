#pragma once
// Introduced in chapter 5
#include "ray.h"

// Updated in chapter 8 to have a material too and also t,n,b
class material;

class hitRecord
{
public:
	float t;
	vec3 p;
	vec3 n;
	vec3 tg, b;
	material* mat;
};

class hitable
{
public:
	material* mat;
	hitable(material* mat = nullptr) : mat(mat) {}
	virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& hitrec) const = 0;
};