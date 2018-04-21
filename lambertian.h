#pragma once
// Introduced in chapter 8
#include "material.h"
#include "sampling.h"

class lambertian : public material
{
public:
	vec3 albedo;
	lambertian(const vec3& albedo) : albedo(albedo) {}
	virtual bool scatter(const ray& r_in, const hitRecord& hitrec, vec3& attenuation, ray& scattered) const
	{
		vec3 cosWeightedDir = uniformCosHemisphere(random(), random());
		// Let E = {(1,0,0), (0,1,0), (0,0,1)} and PinE = {t, n, b}
		// t = t.x*E1 + t.y*E2 + t.z*E3
		// n = n.x*E1 + n.y*E2 + n.z*E3
		// b = b.x*E1 + b.y*E2 + b.z*E3
		// Let q be a point with coordinates in P:
		// q = (q.x, q.y, q.z)
		// qE = q.x*t + q.y*n + q.z*b = q.x*(t.x*E1 + t.y*E2 + t.z*E3) + q.y*... = (t,n,b)*q
		vec3 diffuseDir = vec3(dot(cosWeightedDir, vec3(hitrec.tg.x, hitrec.n.x, hitrec.b.x)),
			dot(cosWeightedDir, vec3(hitrec.tg.y, hitrec.n.y, hitrec.b.y)),
			dot(cosWeightedDir, vec3(hitrec.tg.z, hitrec.n.z, hitrec.b.z)));

		// 0.5 is the albedo here
		scattered = ray(hitrec.p, diffuseDir);
		attenuation = albedo;
		return true;
	}
};