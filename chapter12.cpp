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

static vec3 color(const ray& r, hitable *world, int depth) {
	hitRecord rec;
	if (world->hit(r, 0.001f, FLT_MAX, rec)) {
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat->scatter(r, rec, attenuation, scattered)) {
			return attenuation*color(scattered, world, depth + 1);
		}
		else {
			return vec3(0, 0, 0);
		}
	}
	else {
		vec3 dir = normalize(r.d);
		float t = 0.5*(dir.y + 1.0);
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
	}
}


static hitable *random_scene() {
	int n = 500;
	hitable **list = new hitable*[n + 1];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = random();
			vec3 center(a + 0.9*random(), 0.2, b + 0.9*random());
			if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.8) {  // diffuse
					list[i++] = new sphere(center, 0.2, new lambertian(vec3(random()*random(), random()*random(), random()*random())));
				}
				else if (choose_mat < 0.95) { // metal
					list[i++] = new sphere(center, 0.2,
						new metal(vec3(0.5*(1 + random()), 0.5*(1 + random()), 0.5*(1 + random())), 0.5*random()));
				}
				else {  // glass
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

	return new hitableList(list, i);
}

bool chapter12(const char* filename) {
	int nx = 1200;
	int ny = 800;
	int ns = 10;
	std::ofstream os;
	os.open(filename);
	os << "P3\n" << nx << " " << ny << "\n255\n";
	hitable *list[5];
	float R = cos(M_PI / 4);
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.0));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
	hitable *world = new hitableList(list, 5);
	world = random_scene();

	vec3 lookfrom(13, 2, -30);
	vec3 lookat(0, 0, 0);
	float dist_to_focus = 1.0f;
	float aperture = 0.001f;

	float vfov = 20.0f*float(M_PI) / 180.0f;
	
	thinLensCamera cam = thinLensCamera::fromLookAt(lookfrom, lookat, vec3(0, 1, 0), camera::hfovFromAspect(vfov, float(nx) / float(ny)),
		vfov, dist_to_focus, aperture);

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + random()) / float(nx);
				float v = float(j + random()) / float(ny);
				ray r = cam.getRay(u, v);
				vec3 p = r.at(2.0f);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			os << ir << " " << ig << " " << ib << "\n";
		}
	}
	os.close();
	return true;
}