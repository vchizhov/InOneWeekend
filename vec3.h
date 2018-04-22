// Introduced in chapter 2

#pragma once
#include <math.h>
#include <ostream>

const float epsilon = 0.001f;

class vec3
{
public:
	union
	{
		struct
		{
			float e0, e1, e2;
		};
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
	explicit vec3(float s) : e0(s), e1(s), e2(s) {}
	vec3(float e0, float e1, float e2) : e0(e0), e1(e1), e2(e2) {}
	vec3(const vec3& o) : e0(o.e0), e1(o.e1), e2(o.e2) {}

	vec3& operator=(const vec3& o)
	{
		e0 = o.e0;
		e1 = o.e1;
		e2 = o.e2;
		return *this;
	}

	inline vec3& operator+() { return *this; }
	inline vec3 operator-() const { return vec3(-e0, -e1, -e2); }
	inline const float& operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; }

	inline vec3& operator+=(const vec3& o)
	{
		e0 += o.e0;
		e1 += o.e1;
		e2 += o.e2;
		return *this;
	}
	inline vec3& operator-=(const vec3& o)
	{
		e0 -= o.e0;
		e1 -= o.e1;
		e2 -= o.e2;
		return *this;
	}
	inline vec3& operator*=(const vec3& o)
	{
		e0 *= o.e0;
		e1 *= o.e1;
		e2 *= o.e2;
		return *this;
	}
	inline vec3& operator/=(const vec3& o)
	{
		e0 /= o.e0;
		e1 /= o.e1;
		e2 /= o.e2;
		return *this;
	}
	inline vec3& operator*=(float s)
	{
		e0 *= s;
		e1 *= s;
		e2 *= s;
		return *this;
	}
	inline vec3& operator/=(float s)
	{
		e0 /= s;
		e1 /= s;
		e2 /= s;
		return *this;
	}

	inline float dot(const vec3& o) const
	{
		return e0*o.e0 + e1*o.e1 + e2*o.e2;
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
		return vec3(e1*o.e2 - e2*o.e1, e2*o.e0 - e0*o.e2, e0*o.e1 - e1*o.e0);
	}

	bool operator==(const vec3& o) const
	{
		return e0 == o.e0 && e1 == o.e1 && e2 == o.e2;
	}

	bool operator!=(const vec3& o) const
	{
		return e0 != o.e0 || e1 != o.e1 || e2 != o.e2;
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
float length(const vec3& o);
float lengthSquared(const vec3& o);
vec3 normalize(const vec3& o);
vec3 clamp(const vec3& x, const vec3 a = vec3(0.0f), const vec3 b = vec3(1.0f));
vec3 perp(const vec3& o);
vec3 sqrt(const vec3& o);
vec3 reflect(const vec3& v, const vec3& n);
bool refract(const vec3& v, const vec3& n, float ior, vec3& refracted);
std::ostream& operator<<(std::ostream& os, const vec3& o);
