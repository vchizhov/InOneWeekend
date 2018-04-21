// Introduced in chapter 2

#pragma once
#include <math.h>

class vec3
{
public:
	union
	{
		struct
		{
			float x, y, z;
		};
		struct
		{
			float r, g, b;
		};
		float e[3];
	};

	vec3() {}
	vec3(float s) : x(s), y(s), z(s) {}
	vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	vec3(const vec3& o) : x(o.x), y(o.y), z(o.z) {}

	inline vec3& operator+() { return *this; }
	inline vec3 operator-() { return vec3(-x, -y, -z); }
	inline const float& operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; }

	inline vec3& operator+=(const vec3& o)
	{
		x += o.x;
		y += o.y;
		z += o.z;
		return *this;
	}
	inline vec3& operator-=(const vec3& o)
	{
		x -= o.x;
		y -= o.y;
		z -= o.z;
		return *this;
	}
	inline vec3& operator*=(const vec3& o)
	{
		x *= o.x;
		y *= o.y;
		z *= o.z;
		return *this;
	}
	inline vec3& operator/=(const vec3& o)
	{
		x /= o.x;
		y /= o.y;
		z /= o.z;
		return *this;
	}
	inline vec3& operator*=(float s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	inline vec3& operator/=(float s)
	{
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	inline float dot(const vec3& o) const
	{
		return x*o.x + y*o.y + z*o.z;
	}

	inline float length() const
	{
		return sqrtf(dot(*this));
	}

	inline float lengthSquared() const
	{
		return dot(*this);
	}

	inline vec3& normalize()
	{
		*this /= length();

		return *this;
	}

	inline vec3 cross(const vec3& o) const
	{
		return vec3(y*o.z - z*o.y, z*o.x - x*o.z, x*o.y - y*o.x);
	}

	bool operator==(const vec3& o) const
	{
		return x == o.x && y == o.y && z == o.z;
	}

	bool operator!=(const vec3& o) const
	{
		return x != o.x || y != o.y || z != o.z;
	}
};

vec3 operator+(const vec3& lhs, const vec3& rhs);
vec3 operator-(const vec3& lhs, const vec3& rhs);
vec3 operator*(const vec3& lhs, const vec3& rhs);
vec3 operator/(const vec3& lhs, const vec3& rhs);
vec3 operator*(float lhs, const vec3& rhs);
vec3 operator/(float lhs, const vec3& rhs);
vec3 operator*(const vec3& lhs, float rhs);
vec3 operator/(const vec3& lhs, float rhs);
float dot(const vec3& lhs, const vec3& rhs);
vec3 cross(const vec3& lhs, const vec3& rhs);
vec3 length(const vec3& o);
vec3 lengthSquared(const vec3& o);
vec3 normalize(const vec3& o);
