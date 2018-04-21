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
float length(const vec3& o)
{
	return sqrtf(dot(o, o));
}
float lengthSquared(const vec3& o)
{
	return dot(o, o);
}
vec3 normalize(const vec3& o)
{
	return o / length(o);
}
vec3 clamp(const vec3& x, const vec3 a, const vec3 b)
{
	return vec3(a.x > x.x ? a.x : b.x<x.x ? b.x : x.x, a.y>x.y ? a.y : b.y<x.y ? b.y : x.y, a.z>x.z ? a.z : b.z<x.z ? b.z : x.z);
}
vec3 perp(const vec3& o)
{
	if (o.x < o.y && o.x < o.z) return vec3(0.0f, -o.z, o.y);
	else if (o.y < o.x && o.y < o.z) return vec3(-o.z, 0.0f, o.x);
	else return vec3(-o.y, o.x, 0.0f);
}
vec3 sqrt(const vec3& o)
{
	return vec3(sqrtf(o.x), sqrtf(o.y), sqrtf(o.z));
}
// v + v' = 2i
// v' = 2*i - v = 2*(v+dot(-v,n)*n) - v = v - dot(v,n)
vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2.0f*dot(v, n)*n;
}