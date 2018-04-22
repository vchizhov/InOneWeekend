#pragma once
// Introduced for chapter 8
#include "vec3.h"
class mat3
{
public:
	union
	{
		struct
		{
			vec3 e0, e1, e2;
		};
		struct
		{
			vec3 e[3];
		};
	};

	mat3() {};
	explicit mat3(float s) {}
	mat3(float e00, float e01, float e02, float e10, float e11, float e12, float e20, float e21, float e22)
		: e0(e00, e01, e02), e1(e10, e11, e12), e2(e20, e21, e22) {}
	mat3(float e[3][3]) : e0(e[0][0], e[0][1], e[0][2]), e1(e[1][0], e[1][1], e[1][2]), e2(e[2][0], e[2][1], e[2][2]) {}
	mat3(const vec3& e0, const vec3& e1, const vec3& e2) : e0(e0), e1(e1), e2(e2) {}
	mat3(const mat3& o) : e0(o.e0), e1(o.e1), e2(o.e2) {}
	mat3& operator=(const mat3& o)
	{
		e0 = o.e0;
		e1 = o.e1;
		e2 = o.e2;
		return *this;
	}

	mat3& operator+(const mat3& m)
	{
		return *this;
	}
	mat3 operator-(const mat3& m)
	{
		return mat3(-e0,-e1,-e2);
	}
	vec3& operator[](int i)
	{
		return e[i];
	}
	vec3 operator[](int i) const
	{
		return e[i];
	}

	mat3& operator+=(const mat3& o)
	{
		e0 += o.e0;
		e1 += o.e1;
		e2 += o.e2;
		return *this;
	}
	mat3& operator-=(const mat3& o)
	{
		e0 -= o.e0;
		e1 -= o.e1;
		e2 -= o.e2;
		return *this;
	}
	mat3& operator*=(const mat3& o)
	{
		e0 *= o.e0;
		e1 *= o.e1;
		e2 *= o.e2;
		return *this;
	}
	mat3& operator*=(float s)
	{
		e0 *= s;
		e1 *= s;
		e2 *= s;
		return *this;
	}
	mat3& operator/=(const mat3& o)
	{
		e0 /= o.e0;
		e1 /= o.e1;
		e2 /= o.e2;
		return *this;
	}
	mat3& operator/=(float s)
	{
		e0 /= s;
		e1 /= s;
		e2 /= s;
		return *this;
	}

	bool operator==(const mat3& o)
	{
		return e0 == o.e0 && e1 == o.e1 && e2 == o.e2;
	}

	float det() const
	{
		return e[0][0] * (e[1][1] * e[2][2] - e[1][2] * e[2][1]) +
			e[0][1] * (e[1][2] * e[2][0] - e[1][0] * e[2][2]) +
			e[0][2] * (e[1][0] * e[2][1] - e[1][1] * e[2][0]);
	}

	mat3 transpose() const
	{
		return mat3(vec3(e[0][0], e[1][0], e[2][0]), vec3(e[0][1], e[1][1], e[2][1]), vec3(e[0][2], e[1][2], e[2][2]));
	}

	static mat3 fromColumns(const vec3& e0, const vec3& e1, const vec3& e2);
};

mat3 operator+(const mat3& lhs, const mat3& rhs);
mat3 operator-(const mat3& lhs, const mat3& rhs);
mat3 operator*(const mat3& lhs, const mat3& rhs);
vec3 operator*(const mat3& lhs, const vec3& rhs);
mat3 operator*(float lhs, const mat3& rhs);
mat3 operator/(float lhs, const mat3& rhs);
mat3 operator*(const mat3& lhs, float rhs);
mat3 operator/(const mat3& lhs, float rhs);
float det(const mat3& o);
mat3 transpose(const mat3& o);