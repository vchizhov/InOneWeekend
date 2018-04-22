#include "mat3.h"

mat3 mat3::fromColumns(const vec3& e0, const vec3& e1, const vec3& e2)
{
	return mat3(vec3(e0[0], e1[0], e2[0]), vec3(e0[1], e1[1], e2[1]), vec3(e0[2], e1[2], e2[2]));
}

mat3 operator+(const mat3& lhs, const mat3& rhs)
{
	return mat3(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
}
mat3 operator-(const mat3& lhs, const mat3& rhs)
{
	return mat3(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]);
}
mat3 operator*(const mat3& lhs, const mat3& rhs)
{
	mat3 temp = transpose(rhs);
	return mat3(vec3(dot(lhs[0], rhs[0]), dot(lhs[0], rhs[1]), dot(lhs[0], rhs[2])),
		vec3(dot(lhs[1], rhs[0]), dot(lhs[1], rhs[1]), dot(lhs[1], rhs[2])),
		vec3(dot(lhs[2], rhs[0]), dot(lhs[2], rhs[1]), dot(lhs[2], rhs[2])));
}
vec3 operator*(const mat3& lhs, const vec3& rhs)
{
	return vec3(dot(lhs[0],rhs), dot(lhs[1],rhs), dot(lhs[2],rhs));
}
mat3 operator*(float lhs, const mat3& rhs)
{
	return mat3(lhs*rhs[0], lhs*rhs[1], lhs*rhs[2]);
}
mat3 operator/(float lhs, const mat3& rhs)
{
	return mat3(lhs/rhs[0], lhs/rhs[1], lhs/rhs[2]);
}
mat3 operator*(const mat3& lhs, float rhs)
{
	return mat3(lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs);
}
mat3 operator/(const mat3& lhs, float rhs)
{
	return mat3(lhs[0] / rhs, lhs[1] / rhs, lhs[2] / rhs);
}
float det(const mat3& o)
{
	return o.det();
}
mat3 transpose(const mat3& o)
{
	return o.transpose();
}