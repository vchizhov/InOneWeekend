#pragma once
// Introduced in chapter 8

#include "material.h"

class metal : public material
{
public:
	vec3 albedo;
	float fuzz;
	metal(const vec3& albedo, float fuzz = 0.0f) : albedo(albedo), fuzz(fuzz) {}
	virtual bool scatter(const ray& r_in, const hitRecord& hitrec, vec3& attenuation, ray& scattered) const
	{
		vec3 reflected = reflect(r_in.d, hitrec.n);
		attenuation = albedo;
		if (fuzz == 0.0f)
		{
			scattered = ray(hitrec.p, reflected);
			return true;
		}
		else
		{
			vec3 sampled = uniformCosLobeHemisphere(random(), random(), fuzz);
			vec3 t = normalize(perp(reflected));
			vec3 n = reflected;
			vec3 b = cross(t, n);
			sampled = vec3(dot(sampled, vec3(t.x, n.x, b.x)),
				dot(sampled, vec3(t.y, n.y, b.y)),
				dot(sampled, vec3(t.z, n.z, b.z)));

			scattered = ray(hitrec.p, sampled);
		}
		
		return (dot(reflected, hitrec.n) > 0.0f);
	}
};