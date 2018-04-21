// Introduced in chapter 3
#pragma once

#include "vec3.h"

class ray
{
public:
	vec3 o, d;
	ray() {}
	ray(const vec3& o, const vec3& d) : o(o), d(d) {}
	vec3 at(float t) const { return o + t*d; }
};