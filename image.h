#pragma once

#include "vec3.h"
#include <new>

class Image
{
private:
	vec3* arr;
	int w, h;
public:
	Image() : arr(nullptr), w(0), h(0) {}
	bool init(int width, int height)
	{
		arr = new (std::nothrow) vec3[width*height];
		if (arr == nullptr) return false;
		w = width;
		h = height;
		return true;
	}

	void free()
	{
		if (arr)
		{
			delete[] arr;
			w = 0; h = 0;
		}
	}

	vec3& operator()(int x, int y) { return arr[x + y*w]; }
	vec3 operator()(int x, int y) const { return arr[x + y*w]; }

	~Image()
	{
		free();
	}
};