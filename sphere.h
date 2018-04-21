#pragma once
// Introduced in Chapter 5
#include "hitable.h"

class sphere : public hitable
{
public:
	vec3 center;
	float radius;

public:
	sphere() {}
	sphere(const vec3& c, float r) : center(c), radius(r) {}
	virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& hitrec) const;
};

bool sphere::hit(const ray& r, float tMin, float tMax, hitRecord& hitrec) const
{
	vec3 co = center - r.o;
	float B = dot(r.d, co);
	float C = dot(co, co) - radius*radius;
	float D = B*B - C;
	if (D > 0.0f)
	{
		D = sqrtf(D);
		float t1 = B - D;
		if (t1 > tMin && t1 < tMax)
		{
			hitrec.t = t1;
			hitrec.p = r.at(hitrec.t);
			hitrec.n = (hitrec.p - center) / radius;
			return true;
		}
		float t2 = B + D;
		if (t2 > tMin && t2 < tMax)
		{
			hitrec.t = t2;
			hitrec.p = r.at(hitrec.t);
			hitrec.n = (hitrec.p - center) / radius;
			return true;
		}
	}
	return false;
}