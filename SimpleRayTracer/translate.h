#pragma once
#include "hitable.h"
#include "AABB.h"
class translate :public hitable
{
public:
	hitable *ptr;
	vec3 offset;
	translate(hitable *p, const vec3& displacement):ptr(p),offset(displacement)
	{}
	virtual bool hit(const ray&r, float t_min, float t_max, hit_record &rec)const override;
	virtual bool bounding_box(float t0, float t1, AABB& box)const override;
};

class rotate_y :public hitable
{
public:
	hitable *ptr;
	float sin_theta;
	float cos_theta;
	bool hasbox;
	AABB bbox;
	rotate_y(hitable *p, float angle);
	virtual bool hit(const ray&r, float t_min, float t_max, hit_record &rec)const override;
	virtual bool bounding_box(float t0, float t1, AABB& box)const override

	{
		box = bbox;
		return hasbox;
	}

};