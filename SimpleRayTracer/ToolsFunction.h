#pragma once
#include "vec3.h"

#define  MAX_FLOAT  3.3928236692093846346337460743177e+38f
#define  M_PI 3.1415926535

#define DRAND_M 0x100000000LL  
#define DRAND_C 0xB16  
#define DRAND_A 0x5DEECE66DLL  

double drand(void);

#define  drand48() rand()%10000/10000.0f
class ray;
inline float schlick(float cosine, float ref_idx)
{
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0)*pow((1 - cosine), 5);
}
vec3 random_in_unit_sphere();

vec3 random_on_unit_sphere();

vec3 random_in_unit_disk();
vec3 random_to_sphere(float radius, float distance_squared);

void get_sphere_uv(const vec3 &p, float& u, float &v);


inline vec3 reflect(const vec3 &v,const vec3 &n)
{
	return v - 2 * dot(v, n)*n;
}

inline vec3 random_cosine_direction()
{
	float r1 = drand48();
	float r2 = drand48();

	float  z = sqrt(1 - r2);
	float phi = 2 * M_PI *r1;

	float x = cos(phi) * 2 * sqrt(r2);
	float y = sin(phi) * 2 * sqrt(r2);

	return vec3(x, y, z);
}

inline vec3 de_nan(const vec3 &c)
{
	vec3 temp = c;
	if (temp[0]!=temp[0])
	{
		temp[0] = 0;
	}
	if (temp[1] != temp[1])
	{
		temp[1] = 0;
	}
	if (temp[2] != temp[2])
	{
		temp[2] = 0;
	}
	return temp;
}

bool refract(const vec3&v, const vec3&n, float ni_over_nt, vec3& refracted);

bool IntersetTriangle(const ray & ray_in, const vec3& v0, const vec3& v1,const vec3& v2, vec3 & hit_point);

vec3 ConstructNormal(vec3& v0, vec3& v1, vec3& v2);
