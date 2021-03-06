#pragma once

// Introduced in chapter 8

#include "vec3.h"

vec3 uniformCosHemisphere(float r1, float r2);
vec3 uniformCosLobeHemisphere(float r1, float r2, float lobeTheta);
vec3 uniformDisk(float r1, float r2);

float random();