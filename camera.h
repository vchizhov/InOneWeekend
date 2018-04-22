#pragma once

//Introduced in chapter 6
// Updated in chapter 10
#include "ray.h"
#include "sampling.h"
#include "mat3.h"
class camera
{
protected:
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

class thinLensCamera : public camera
{
private:
	float filmDistance;
	float apertureRadius;
public:
	thinLensCamera() {}
	thinLensCamera(vec3 origin, vec3 right, vec3 up, vec3 forward, float hfov, float vfov, float fd, float ar)
		: camera(origin, right, up, forward, hfov, vfov), filmDistance(fd), apertureRadius(ar) {}
	thinLensCamera(const camera& cam, float fd, float ar) : camera(cam), filmDistance(fd), apertureRadius(ar) {}

	static thinLensCamera fromLookAt(vec3 origin, vec3 target, vec3 vup, float hfov, float vfov, float fd, float ar)
	{
		return thinLensCamera(camera::fromLookAt(origin, target, vup, hfov, vfov), fd, ar);
	}

	ray getRay(float ndcX, float ndcY)
	{
		vec3 sampled = apertureRadius*uniformDisk(random(), random());
		sampled = sampled.x*right + sampled.y*up;
		vec3 filmPixel = scaleX*ndcX*right + scaleY*ndcY*up + filmDistance*forward;
		vec3 dir = normalize(filmPixel - sampled);
		return ray(origin + sampled, dir);
	}
};