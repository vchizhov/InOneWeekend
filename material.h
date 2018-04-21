#pragma once

// Introduced in chapter 8
#include "hitable.h"

class material
{
public:
	virtual bool scatter(const ray& r_in, const hitRecord& rec, vec3& attenuation, ray& scattered) const = 0;
};