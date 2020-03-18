#pragma once
#include "hitable.h"
class material;
class moving_sphere :public hitable
{
public:
	vec3 center0,center1;
	material *mat_ptr;
	float time0, time1;
	float radius;
	moving_sphere(){}
	moving_sphere(vec3 cen0,vec3 cen1 ,float t0,float t1,float r,material*m):
	center0(cen0),center1(cen1),time0(t0),time1(t1), radius(r),mat_ptr(m)
	{}

	virtual bool hit(const ray&r, float t_min, float t_max, hit_record &rec)const override;
	virtual bool bounding_box(float t0, float t1, AABB& box)const;
	vec3 center(float time)const
	{
		return center0 + ((time - time0) / (time1 - time0))*(center1 - center0);
	}
	
};

