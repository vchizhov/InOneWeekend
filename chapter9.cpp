#include "chapters.h"
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"
#include <fstream>

static vec3 color(const ray& o, const hitableList& world, int depth)
{
	hitRecord hitrec;
	if (world.hit(o, 0.0f, FLT_MAX, hitrec))
	{
		ray scattered;
		vec3 attenuation;
		if (depth < 10 && hitrec.mat->scatter(o, hitrec, attenuation, scattered))
		{
			return attenuation*color(scattered, world, depth + 1);
		}
		else
		{
			return vec3(0.0f);
		}

	}
	else
	{
		//[-1,1]->[0,1]
		float s = 0.5f*(o.d.y + 1.0f);
		// lerp b etween white and sky blue - the closer to the horizon the ray is, the whiter
		return (1 - s)*vec3(1.0f) + s*vec3(0.5f, 0.7f, 1.0f);
	}
}

bool chapter9(const char* filename)
{
	int nx = 800;
	int ny = 400;
	int ns = 20;
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


	hitable* list[5];
	list[0] = new sphere(vec3(0.0f, 0.0f, 1.0f), 0.5f, new lambertian(vec3(0.1f, 0.2f, 0.5f)));
	list[1] = new sphere(vec3(0.0f, -100.5f, 0.0f), 100.0f, new lambertian(vec3(0.8f, 0.8f, 0.0f)));
	list[2] = new sphere(vec3(1.0f, 0.0f, 1.0f), 0.5f, new metal(vec3(0.8f, 0.6f, 0.2f)));
	list[3] = new sphere(vec3(-1.0f, 0.0f, 1.0f), 0.5f, new dielectric(1.5f));
	list[4] = new sphere(vec3(-1.0f, 0.0f, 1.0f), 0.45f, new dielectric(1.0f/1.5f));
	hitableList world(list, 5);

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
				col += color(r, world, 0);
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