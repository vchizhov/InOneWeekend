#include "vec3.h"

vec3 operator+(const vec3& lhs, const vec3& rhs)
{
	return vec3(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
}
vec3 operator-(const vec3& lhs, const vec3& rhs)
{
	return vec3(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]);
}
vec3 operator*(const vec3& lhs, const vec3& rhs)
{
	return vec3(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]);
}
vec3 operator/(const vec3& lhs, const vec3& rhs)
{
	return vec3(lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2]);
}
vec3 operator*(float lhs, const vec3& rhs)
{
	return vec3(lhs * rhs[0], lhs * rhs[1], lhs * rhs[2]);
}
vec3 operator/(float lhs, const vec3& rhs)
{
	return vec3(lhs / rhs[0], lhs / rhs[1], lhs / rhs[2]);
}
vec3 operator*(const vec3& lhs, float rhs)
{
	return vec3(lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs);
}
vec3 operator/(const vec3& lhs, float rhs)
{
	return vec3(lhs[0] / rhs, lhs[1] / rhs, lhs[2] / rhs);
}
float dot(const vec3& lhs, const vec3& rhs)
{
	return lhs[0]*rhs[0] + lhs[1]*rhs[1] + lhs[2]*rhs[2];
}
vec3 cross(const vec3& lhs, const vec3& rhs)
{
	return vec3(lhs[1]*rhs[2] - lhs[2]*rhs[1], lhs[2]*rhs[0] - lhs[0]*rhs[2], lhs[0]*rhs[1] - lhs[1]*rhs[0]);
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
	return vec3(a[0] > x[0] ? a[0] : b[0]<x[0] ? b[0] : x[0], a[1]>x[1] ? a[1] : b[1]<x[1] ? b[1] : x[1], a[2]>x[2] ? a[2] : b[2]<x[2] ? b[2] : x[2]);
}
vec3 perp(const vec3& o)
{
	if (o[0] < o[1] && o[0] < o[2]) return vec3(0.0f, -o[2], o[1]);
	else if (o[1] < o[0] && o[1] < o[2]) return vec3(-o[2], 0.0f, o[0]);
	else return vec3(-o[1], o[0], 0.0f);
}
vec3 sqrt(const vec3& o)
{
	return vec3(sqrtf(o[0]), sqrtf(o[1]), sqrtf(o[2]));
}
// v + v' = 2i
// v' = 2*i - v = 2*(v+dot(-v,n)*n) - v = v - dot(v,n)
vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2.0f*dot(v, n)*n;
}
bool refract(const vec3& v, const vec3& n, float ior, vec3& refracted)
{
	float cosTheta1 = -dot(v, n);
	float cosTheta2Sq = 1.0f - ior*ior*(1.0f - cosTheta1*cosTheta1);
	if (cosTheta2Sq < 0.0f) return false;
	else
	{
		refracted = ior*v + (cosTheta1*ior - sqrtf(cosTheta2Sq))*n;
		return true;
	}
}
std::ostream& operator<<(std::ostream& os, const vec3& o)
{
	os << o[0] << "\t" << o[1] << "\t" << o[2];
}