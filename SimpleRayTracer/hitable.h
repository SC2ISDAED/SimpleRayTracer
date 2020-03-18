#pragma once
#include "ray.h"

class material;
class AABB;
struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;
	material * mat_ptr;
	float u, v;
};

class hitable {
public:
	virtual bool hit(const ray&r, float t_min, float t_max, hit_record &rec)const = 0;
	virtual bool bounding_box(float t0, float t1, AABB& box)const = 0;

	virtual float pdf_value(const vec3& o, const vec3 &v)const { return 0.0f; }
	virtual vec3 random(const vec3& o)const
	{
		return vec3(1, 0, 0);
	}
};