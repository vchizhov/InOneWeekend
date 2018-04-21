#pragma once
// Introduced in chapter 8

#include "material.h"

class metal : public material
{
public:
	vec3 albedo;
	metal(const vec3& albedo) : albedo(albedo) {}
	virtual bool scatter(const ray& r_in, const hitRecord& hitrec, vec3& attenuation, ray& scattered) const
	{
		vec3 reflected = reflect(r_in.d, hitrec.n);
		scattered = ray(hitrec.p, reflected);
		attenuation = albedo;
		return (dot(reflected, hitrec.n) > 0.0f);
	}
};