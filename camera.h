#pragma once

//Introduced in chapter 6
#include "ray.h"
class camera
{
private:
	vec3 origin;
	vec3 right, up, forward;
	float aspectRatio;
public:
	camera() {}
	camera(vec3 origin, vec3 right, vec3 up, vec3 forward, float aspectRatio) : origin(origin), right(right), up(up), forward(forward), aspectRatio(aspectRatio) {}
	ray getRay(float ndcX, float ndcY)
	{
		return ray(origin, normalize(aspectRatio*ndcX*right + ndcY*up + forward));
	}

};