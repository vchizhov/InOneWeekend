#include "vec3.h"

vec3 operator+(const vec3& lhs, const vec3& rhs)
{
	return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}
vec3 operator-(const vec3& lhs, const vec3& rhs)
{
	return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}
vec3 operator*(const vec3& lhs, const vec3& rhs)
{
	return vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}
vec3 operator/(const vec3& lhs, const vec3& rhs)
{
	return vec3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}
vec3 operator*(float lhs, const vec3& rhs)
{
	return vec3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}
vec3 operator/(float lhs, const vec3& rhs)
{
	return vec3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
}
vec3 operator*(const vec3& lhs, float rhs)
{
	return vec3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}
vec3 operator/(const vec3& lhs, float rhs)
{
	return vec3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}
float dot(const vec3& lhs, const vec3& rhs)
{
	return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}
vec3 cross(const vec3& lhs, const vec3& rhs)
{
	return vec3(lhs.y*rhs.z - lhs.z*rhs.y, lhs.z*rhs.x - lhs.x*rhs.z, lhs.x*rhs.y - lhs.y*rhs.x);
}
vec3 length(const vec3& o)
{
	return sqrtf(dot(o, o));
}
vec3 lengthSquared(const vec3& o)
{
	return dot(o, o);
}
vec3 normalize(const vec3& o)
{
	return o / length(o);
}