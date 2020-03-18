#pragma once
#include "hitable.h"
#include "Isotropic.h"
class texture;
class constant_medium :public hitable
{
public:
	hitable * boundary;
	float density;
	material * phase_function;
	constant_medium(hitable *b, float d, texture *_tex) :boundary(b),density(d)
	{
		phase_function = new Isotropic(_tex);
	}
	virtual bool bounding_box(float t0, float t1, AABB& box)const override;
	virtual bool hit(const ray&r, float t_min, float t_max, hit_record &rec)const override;
};