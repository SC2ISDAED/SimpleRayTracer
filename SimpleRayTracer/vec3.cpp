#include "vec3.h"

vec3& vec3::operator+=(const vec3 &v2)
{
	e[0] += v2[0];
	e[1] += v2[1];
	e[2] += v2[2];
	return *this;
}


vec3& vec3::operator-=(const vec3 &v2)
{
	e[0] -= v2[0];
	e[1] -= v2[1];
	e[2] -= v2[2];
	return *this;
}


vec3& vec3::operator=(const vec3&vt)
{
	e[0] = vt[0];
	e[1] = vt[1];
	e[2] = vt[2];
	return *this;
}

vec3& vec3::operator/=(const float t)
{
	e[0] /= t;
	e[1] /= t;
	e[2] /= t;
	return *this;
}

vec3& vec3::operator/=(const vec3 &v2)
{
	e[0] /= v2[0];
	e[1] /= v2[1];
	e[2] /= v2[2];
	return *this;
}



vec3& vec3::operator*=(const float t)
{
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

vec3& vec3::operator*=(const vec3 &v2)
{
	e[0] *= v2[0];
	e[1] *= v2[1];
	e[2] *= v2[2];
	return *this;
}



