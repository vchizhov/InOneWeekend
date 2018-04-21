#include "chapters.h"
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include <fstream>

// Integral{cos(theta)*sin(theta) d(theta)d(phi)}
static vec3 uniformCosHemisphere(float r1, float r2)
{
	float phi = 2.0f*float(M_PI)*r1;
	float sinTheta = sqrtf(r2);
	float cosTheta = sqrtf(1.0f - r2);
	return vec3(sinTheta*cosf(phi), cosTheta, sinTheta*sinf(phi));
}


static std::mt19937 genG(std::random_device{}());
static std::uniform_real_distribution<float> distG(0.0f, 1.0f);

static vec3 color(const ray& o, const hitableList& world)
{
	hitRecord hitrec;
	if (world.hit(o, 0.0f, FLT_MAX, hitrec))
	{
		vec3 cosWeightedDir = uniformCosHemisphere(distG(genG), distG(genG));
		vec3 t = normalize(perp(hitrec.n));
		vec3 b = cross(hitrec.n, t);
		// Let E = {(1,0,0), (0,1,0), (0,0,1)} and PinE = {t, n, b}
		// t = t.x*E1 + t.y*E2 + t.z*E3
		// n = n.x*E1 + n.y*E2 + n.z*E3
		// b = b.x*E1 + b.y*E2 + b.z*E3
		// Let q be a point with coordinates in P:
		// q = (q.x, q.y, q.z)
		// qE = q.x*t + q.y*n + q.z*b = q.x*(t.x*E1 + t.y*E2 + t.z*E3) + q.y*... = (t,n,b)*q
		vec3 diffuseDir = vec3(dot(cosWeightedDir, vec3(t.x, hitrec.n.x, b.x)), 
			dot(cosWeightedDir, vec3(t.y, hitrec.n.y, b.y)), 
			dot(cosWeightedDir, vec3(t.z, hitrec.n.z, b.z)));

		// 0.5 is the albedo here
		return 0.5f*color(ray(hitrec.p, diffuseDir), world);
	}
	else
	{
		//[-1,1]->[0,1]
		float s = 0.5f*(o.d.y + 1.0f);
		// lerp b etween white and sky blue - the closer to the horizon the ray is, the whiter
		return (1 - s)*vec3(1.0f) + s*vec3(0.5f, 0.7f, 1.0f);
	}
}

bool chapter7(const char* filename)
{
	int nx = 200;
	int ny = 100;
	int ns = 100;
	float aspectRatio = float(nx) / float(ny);
	std::ofstream os;

	std::mt19937 gen(std::random_device{}());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);


	// camera axes
	vec3 right(1.0f, 0.0f, 0.0f);
	vec3 up(0.0f, 1.0f, 0.0f);
	vec3 forward = cross(normalize(right), normalize(up));
	vec3 origin(0.0f);
	camera cam(origin, right, up, forward, aspectRatio);


	hitable* list[2];
	list[0] = new sphere(vec3(0.0f, 0.0f, 1.0f), 0.5f);
	list[1] = new sphere(vec3(0.0f, -100.5f, 0.0f), 100.0f);
	hitableList world(list, 2);

	os.open(filename);
	os << "P3\n" << nx << " " << ny << "\n255\n";
	for (int y = ny - 1; y >= 0; --y)
		for (int x = 0; x < nx; ++x)
		{
			vec3 col(0.0f);
			for (int s = 0; s < ns; ++s)
			{
				// map the pixels to [-1,1]^2 such that they are centered(pixel (i,j)'s center is actually at (i+1/2, j+1/2))
				float ndcX = 2.0f*(float(x) + dist(gen)) / float(nx) - 1.0f;
				float ndcY = 2.0f*(float(y) + dist(gen)) / float(ny) - 1.0f;
				ray r = cam.getRay(ndcX, ndcY);
				col += color(r, world);
			}
			col /= float(ns);
			col = sqrt(col);
			col = clamp(col);

			// map from [0,1] to [0,255]
			int ir = int(255.99f*col.r);
			int ig = int(255.99f*col.g);
			int ib = int(255.99f*col.b);

			os << ir << " " << ig << " " << ib << "\n";
		}
	os.close();

	return true;
}