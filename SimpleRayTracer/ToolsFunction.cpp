#include "ToolsFunction.h"
#include "ray.h"
bool refract(const vec3&v, const vec3&n, float ni_over_nt, vec3& refracted)
{
	vec3 uv = make_unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt*(1 - dt * dt);//1.0-n^2(1.0-cosn^2)
	if (discriminant > 0)
	{
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else
	{
		return false;
	}
}

bool IntersetTriangle(const ray & ray_in, const vec3& v0, const vec3& v1, const vec3& v2, vec3 & hit_point)
{
		// E1
		vec3 E1 = v1 - v0;

		// E2
		vec3 E2 = v2 - v0;

		// P
		vec3 P = cross(ray_in.direction, E2);

		// determinant
		float det = dot(E1, P);

		// keep det > 0, modify T accordingly
		vec3 T;
		if (det > 0)
		{
			T = ray_in.origin - v0;
		}
		else
		{
			T = v0 - ray_in.origin;
			det = -det;
		}

		// If determinant is near zero, ray lies in plane of triangle
		if (det < 0.0001f)
			return false;

		// Calculate u and make sure u <= 1
		float u = dot(T, P);
		if (u < 0.0f || u > det)
			return false;

		// Q
		vec3 Q = cross(E1, T);

		// Calculate v and make sure u + v <= 1
		float v = dot(Q, ray_in.direction);
		if (v < 0.0f || u + v > det)
			return false;

		// Calculate t, scale parameters, ray intersects triangle
		float t = dot(E2, Q);

		float fInvDet = 1.0f / det;
		t *= fInvDet;
		u *= fInvDet;
		v *= fInvDet;

		hit_point = vec3(t, u, v);
		return true;
}



vec3 ConstructNormal(vec3& v0, vec3& v1, vec3& v2)
{
	vec3 E1 = v0 - v1;
	vec3 E2 = v0 - v2;
	return vec3(cross(E1, E2));
}

double drand(void)
{

	unsigned long long seed = 1;
	seed = (DRAND_A * seed + DRAND_C) & 0xFFFFFFFFFFFFLL;
	unsigned int x = seed >> 16;
	return  ((double)x / (double)DRAND_M);


}

vec3 random_in_unit_sphere()
{
	vec3 p;
	do
	{
		p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}

vec3 random_on_unit_sphere()
{
	vec3 p;
	do
	{
		p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
	} while (dot(p, p) >= 1.0);
	return make_unit_vector(p);
}

vec3 random_in_unit_disk()
{
	vec3 p;
	do
	{
		p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
	} while (dot(p, p) >= 1.0);
	return p;
}

vec3 random_to_sphere(float radius, float distance_squared)
{
	float r1 = drand48();
	float r2 = drand48();

	float z = 1 + r2 * (sqrt(1 - radius * radius / distance_squared) - 1);
	float phi = 2 * M_PI *r1;
	float x = cos(phi)*sqrt(1 - z * z);
	float y = sin(phi)*sqrt(1 - z * z);

	return vec3(x, y, z);
}

void get_sphere_uv(const vec3 &p, float& u, float &v)
 {

	 float phi = atan2(p.z(), p.x());
	 float theta = asin(p.y());
	 u = 1 - (phi + M_PI) / (2 * M_PI);
	 v = (theta + M_PI / 2) / M_PI;

 }
