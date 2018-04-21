#include "chapters.h"
#include <fstream>
#include "vec3.h"

bool chapter2(const char* filename)
{
	int nx = 200;
	int ny = 100;

	std::ofstream os;
	os.open(filename);

	os << "P3\n" << nx << " " << ny << "\n255\n";
	for (int y = ny - 1; y >= 0; --y)
		for (int x = 0; x < nx; ++x)
		{
			vec3 col(float(x) / float(nx), float(y) / float(ny), 0.2f);
			// map from [0,1) to [0,256)
			int ir = int(256.0f*col.r);
			int ig = int(256.0f*col.g);
			int ib = int(256.0f*col.b);
			os << ir << " " << ig << " " << ib << "\n";
		}

	os.close();
	return true;
}