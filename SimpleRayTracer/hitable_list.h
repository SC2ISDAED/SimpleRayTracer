#pragma once
#include "hitable.h"
class hitable_list :public hitable
{
public:
	hitable ** list;
	int list_size;
	hitable_list(){}
	hitable_list(hitable **l, int n)
	{
		list = l;
		list_size = n;
	}

	virtual bool hit(const ray&r, float t_min, float t_max, hit_record &rec)const override;
	bool bounding_box(float t0, float t1, AABB& box)const override;
	float pdf_value(const vec3& o, const vec3 &v)const override;
	virtual vec3 random(const vec3& o)const override;
};

