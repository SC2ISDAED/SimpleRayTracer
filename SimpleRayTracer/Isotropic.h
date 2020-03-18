#pragma once
#include "Material.h"
#include "ToolsFunction.h"
#include "texture.h"
class Isotropic :public material
{
public:
	texture * albedo;
	Isotropic(texture *a):albedo(a){}
	virtual bool scatter(const ray& r_in, const hit_record & rec,
		Scatter_Record& srec)const override
	{
		srec.specular_ray = ray(rec.p, random_in_unit_sphere());
		srec.attenuation = albedo->value(rec.u, rec.v, rec.p);
		return true;
	}
};
