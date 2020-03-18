#pragma once
#include "Material.h"
#include "texture.h"
class texture;
class Diffuse_Light :public material
{
public:
	texture * emit;
	Diffuse_Light(texture * tex):emit(tex)
	{}
	virtual bool scatter(const ray& r_in, const hit_record & rec,
		Scatter_Record& srec)const override;
	virtual vec3 emitted(const ray& r_in, const hit_record& rec, float u, float v, const vec3& p)const override
	{
		if (dot(rec.normal, r_in.direction) < 0.0)
		{
			return emit->value(u, v, p);
		}
		return emit->value(u, v, p);
	}

};