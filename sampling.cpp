#include "sampling.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "vec3.h"
#include <random>

vec3 uniformCosHemisphere(float r1, float r2)
{
	float phi = 2.0f*float(M_PI)*r1;
	float sinTheta = sqrtf(r2);
	float cosTheta = sqrtf(1.0f - r2);
	return vec3(sinTheta*cosf(phi), cosTheta, sinTheta*sinf(phi));
}

vec3 uniformCosLobeHemisphere(float r1, float r2, float lobeTheta)
{
	float phi = 2.0f*float(M_PI)*r1;
	float lb = sinf(lobeTheta);
	float sinTheta = sqrtf(r2*lb*lb);
	float cosTheta = sqrtf(1.0f - r2);
	return vec3(sinTheta*cosf(phi), cosTheta, sinTheta*sinf(phi));
}

vec3 uniformDisk(float r1, float r2)
{
	float phi = 2.0f*float(M_PI)*r1;
	float r = sqrtf(r2);
	return vec3(r*cosf(phi), r*sinf(phi), 0.0f);
}

float random()
{
	static thread_local std::mt19937 gen(std::random_device{}());
	static thread_local std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	return dist(gen);
}