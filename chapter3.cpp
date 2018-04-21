#include "chapters.h"

#include <fstream>
#include "ray.h"

static vec3 color(const ray& o)
{
	//[-1,1]->[0,1]
	float t = 0.5f*(o.d.y + 1.0f);
	// lerp b etween white and sky blue - the closer to the horizon the ray is, the whiter
	return (1-t)*vec3(1.0f) + t*vec3(0.5f, 0.7f, 1.0f);
}

bool chapter3(const char* filename)
{
	int nx = 200;
	int ny = 100;

	std::ofstream os;
	os.open(filename);

	os << "P3\n" << nx << " " << ny << "\n255\n";

	// camera axes
	vec3 right(1.0f,0.0f,0.0f);
	vec3 up(0.0f, 1.0f, 0.0f);
	vec3 forward = cross(normalize(right), normalize(up));
	vec3 origin(0.0f);

	for (int y = ny - 1; y >= 0; --y)
		for (int x = 0; x < nx; ++x)
		{
			// map the pixels to [-1,1]^2 such that they are centered(pixel (i,j)'s center is actually at (i+1/2, j+1/2))
			float ndcX = 2.0f*(float(x) + 0.5f) / float(nx) - 1.0f;
			float ndcY = 2.0f*(float(y) + 0.5f) / float(ny) - 1.0f;
			ray r(origin, normalize(ndcX*right + ndcY*up + forward));
			vec3 col = clamp(color(r));
			// map from [0,1] to [0,255]
			int ir = int(255.99f*col.r);
			int ig = int(255.99f*col.g);
			int ib = int(255.99f*col.b);
			os << ir << " " << ig << " " << ib << "\n";
		}

	os.close();
	return true;
}