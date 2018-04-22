#pragma once

// Introduced in chapter 8
#include "hitable.h"
#include "sampling.h"
#include "mat3.h"

class material
{
public:
	virtual bool scatter(const ray& r_in, const hitRecord& rec, vec3& attenuation, ray& scattered) const = 0;
};

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
		vec3 diffuseDir = mat3::fromColumns(hitrec.tg, hitrec.n, hitrec.b)*cosWeightedDir;

		float cs = dot(r_in.d, hitrec.n);
		vec3 normal = cs < 0.0f ? hitrec.n : -hitrec.n;

		scattered = ray(hitrec.p + epsilon*hitrec.n, diffuseDir);
		attenuation = albedo;
		return true;
	}
};

class metal : public material
{
public:
	vec3 albedo;
	float fuzz;
	metal(const vec3& albedo, float fuzz = 0.0f) : albedo(albedo), fuzz(fuzz) {}
	virtual bool scatter(const ray& r_in, const hitRecord& hitrec, vec3& attenuation, ray& scattered) const
	{
		float cs = dot(r_in.d, hitrec.n);
		vec3 normal = cs < 0.0f ? hitrec.n : -hitrec.n;
		vec3 reflected = reflect(r_in.d, normal);
		attenuation = albedo;
		
		// perfect mirror
		if (fuzz == 0.0f)
		{
			scattered = ray(hitrec.p + epsilon*normal, reflected);
			return true;
		}
		else // fuzzy mirror
		{
			vec3 sampled = uniformCosLobeHemisphere(random(), random(), fuzz);
			vec3 t = normalize(perp(reflected));
			vec3 n = reflected;
			vec3 b = cross(t, n);
			sampled = mat3::fromColumns(t, n, b)*sampled;

			scattered = ray(hitrec.p + epsilon*normal, sampled);
			return (dot(reflected, hitrec.n) > 0.0f);
		}
		
	}
};

static float schlick(float cosine, float ref_idx) {
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0*r0;
	return r0 + (1 - r0)*powf((1 - cosine), 5);
}

class dielectric : public material
{
public:
	float ior;
	dielectric(float ior) : ior(ior) {}
	virtual bool scatter(const ray& r_in, const hitRecord& hitrec, vec3& attenuation, ray& scattered) const
	{
		float cosTheta = dot(r_in.d, hitrec.n);
		vec3 normal;
		float tempIOR;
		float schlickCosTheta;

		if (cosTheta > 0.0f)
		{
			normal = -hitrec.n;
			tempIOR = ior;
			schlickCosTheta = sqrtf(1.0f - tempIOR*tempIOR*(1.0f - cosTheta*cosTheta));
		}
		else
		{
			normal = hitrec.n;
			tempIOR = 1.0f / ior;
			schlickCosTheta = -cosTheta;
		}
		vec3 refracted;
		float reflectProb;
		
		if (refract(r_in.d, normal, tempIOR, refracted))
		{
			// schlick(schlickCosTheta, tempIOR) == schlick(schlickCosTheta, 1.0f/tempIOR);
			reflectProb = schlick(schlickCosTheta, tempIOR);
		}
		else
			reflectProb = 1.0f;

		if (random() < reflectProb)
		{
			attenuation = vec3(1.0f, 1.0f, 1.0f);
			vec3 reflected = reflect(r_in.d, normal);
			scattered = ray(hitrec.p + epsilon*normal, reflected);
		}
		else
		{
			attenuation = vec3(1.0f);
			scattered = ray(hitrec.p - epsilon*normal, refracted);
		}
		return true;
	}
};