#include "chapters.h"

#include <fstream>
#include <string>
#include "ray.h"
#include "hitable_list.h"
#include "sphere.h"

static float hitSphere(const vec3& center, float radius, const ray& r)
{
	// |r(t) - center|^2 = radius^2
	// |ro - center|^2 + 2*t*dot(rd, ro - center) + t^2*dot(rd,rd) = radius^2
	// t^2*dot(rd,rd) - 2*t*dot(rd,center-ro) + |center-ro|^2 - radius^2 = 0
	// A = dot(rd,rd), B = dot(rd,center-ro), C = |center-ro|^2 - radius^2
	// A*t^2 - 2*B + C = 0
	// D = B^2 - A*C
	// t1,2 = (B +- sqrt(D))/A
	// set |rd| = 1 -> A = 1
	vec3 co = center - r.o;
	float B = dot(r.d, co);
	float C = dot(co, co) - radius*radius;
	float D = B*B - C;
	if (D < 0.0f) return -1.0f; else return B - D;
	return true;
}

static vec3 color1(const ray& o)
{
	float t = hitSphere(vec3(0, 0, 1), 0.5f, o);
	if (t > 0.0f)
	{
		vec3 normal = normalize(o.at(t) - vec3(0, 0, 1));
		// note: I use a convention such that the camera's coordinate system is X x Y = Z
		// whereas the used convention in the book is X x Y = -Z
		// Basically I am using a right-handed coordinate system, since it is consistent with the usual mathematical notation for quaternions: ixj=k
		// While a left-handed coordinate system is used in the book
		// That's why to get the colors from the book I need to flip the z component
		normal.z = -normal.z;
		return 0.5f*(normal + vec3(1.0f));
	}
	////[-1,1]->[0,1]
	float s = 0.5f*(o.d.y + 1.0f);
	//// lerp b etween white and sky blue - the closer to the horizon the ray is, the whiter
	return (1 - s)*vec3(1.0f) + s*vec3(0.5f, 0.7f, 1.0f);

}

static vec3 color2(const ray& o, hitableList& world)
{
	float t = hitSphere(vec3(0, 0, 1), 0.5f, o);
	hitRecord hitrec;
	if (world.hit(o, 0.0f, FLT_MAX, hitrec))
	{
		hitrec.n.z = -hitrec.n.z;
		return 0.5f*(hitrec.n + vec3(1.0f));
	}
	else
	{
		//[-1,1]->[0,1]
		float s = 0.5f*(o.d.y + 1.0f);
		// lerp b etween white and sky blue - the closer to the horizon the ray is, the whiter
		return (1 - s)*vec3(1.0f) + s*vec3(0.5f, 0.7f, 1.0f);
	}
}

bool chapter5(const char* filename)
{
	int nx = 200;
	int ny = 100;
	float aspectRatio = float(nx) / float(ny);
	std::ofstream os;
	

	

	// camera axes
	vec3 right(1.0f, 0.0f, 0.0f);
	vec3 up(0.0f, 1.0f, 0.0f);
	vec3 forward = cross(normalize(right), normalize(up));
	vec3 origin(0.0f);

	std::string fullFilename;

	fullFilename = filename;
	fullFilename += "_img1.ppm";
	os.open(fullFilename);
	os << "P3\n" << nx << " " << ny << "\n255\n";
	for (int y = ny - 1; y >= 0; --y)
		for (int x = 0; x < nx; ++x)
		{
			// map the pixels to [-1,1]^2 such that they are centered(pixel (i,j)'s center is actually at (i+1/2, j+1/2))
			float ndcX = 2.0f*(float(x) + 0.5f) / float(nx) - 1.0f;
			float ndcY = 2.0f*(float(y) + 0.5f) / float(ny) - 1.0f;
			ray r(origin, normalize(aspectRatio*ndcX*right + ndcY*up + forward));
			vec3 col = clamp(color1(r));
			// map from [0,1] to [0,255]
			int ir = int(255.99f*col.r);
			int ig = int(255.99f*col.g);
			int ib = int(255.99f*col.b);
			
			os << ir << " " << ig << " " << ib << "\n";
		}
	os.close();

	hitable* list[2];
	list[0] = new sphere(vec3(0.0f, 0.0f, 1.0f), 0.5f);
	list[1] = new sphere(vec3(0.0f, -100.5f, 0.0f), 100.0f);
	hitableList world(list, 2);

	fullFilename = filename;
	fullFilename += "_img2.ppm";
	os.open(fullFilename);
	os << "P3\n" << nx << " " << ny << "\n255\n";
	for (int y = ny - 1; y >= 0; --y)
		for (int x = 0; x < nx; ++x)
		{
			// map the pixels to [-1,1]^2 such that they are centered(pixel (i,j)'s center is actually at (i+1/2, j+1/2))
			float ndcX = 2.0f*(float(x) + 0.5f) / float(nx) - 1.0f;
			float ndcY = 2.0f*(float(y) + 0.5f) / float(ny) - 1.0f;
			ray r(origin, normalize(aspectRatio*ndcX*right + ndcY*up + forward));
			vec3 col = clamp(color2(r, world));
			// map from [0,1] to [0,255]
			int ir = int(255.99f*col.r);
			int ig = int(255.99f*col.g);
			int ib = int(255.99f*col.b);

			os << ir << " " << ig << " " << ib << "\n";
		}
	os.close();

	return true;
}