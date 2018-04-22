#pragma once

//Introduced in chapter 6
// Updated in chapter 10
#include "ray.h"
class camera
{
private:
	vec3 origin;
	vec3 right, up, forward;
	float scaleX, scaleY;
public:
	camera() {}
	camera(vec3 origin, vec3 right, vec3 up, vec3 forward, float aspectRatio) : origin(origin), right(right), up(up), forward(forward), scaleX(aspectRatio), scaleY(1.0f) {}
	camera(vec3 origin, vec3 right, vec3 up, vec3 forward, float hfov, float vfov)
		: origin(origin), right(right), up(up), forward(forward), scaleX(tanf(0.5f*hfov)), scaleY(tanf(0.5f*vfov))
	{
	}

	camera(const camera& o) : origin(o.origin), right(o.right), up(o.up), forward(o.forward), scaleX(o.scaleX), scaleY(o.scaleY) {}
	camera& operator=(const camera& o)
	{
		origin = o.origin;
		right = o.right;
		up = o.up;
		forward = o.forward;
		scaleX = o.scaleX;
		scaleY = o.scaleY;
		return *this;
	}
	
	ray getRay(float ndcX, float ndcY)
	{
		return ray(origin, normalize(scaleX*ndcX*right + scaleY*ndcY*up + forward));
	}

	static camera fromLookAt(vec3 origin, vec3 target, vec3 vup, float hfov, float vfov)
	{
		vec3 forward1 = normalize(target - origin);
		vec3 right1 = normalize(cross(normalize(vup), forward1));
		vec3 up1 = cross(forward1, right1);
		return camera(origin, right1, up1, forward1, hfov, vfov);
	}

	static float vfovFromAspect(float hfov, float aspectRatio)
	{
		float x = tanf(0.5f*hfov);
		float y = x / aspectRatio;
		float vfov = 2.0f*atanf(y);
		return vfov;
	}

	static float hfovFromAspect(float vfov, float aspectRatio)
	{
		float y = tanf(0.5f*vfov);
		float x = y * aspectRatio;
		float hfov = 2.0f*atanf(x);
		return hfov;
	}

};