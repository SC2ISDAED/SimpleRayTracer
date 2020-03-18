#pragma once
#include "ray.h"
#include "Material.h"
#include "ToolsFunction.h"
#include "texture.h"


class Lambertian :public material
{
public:
	Lambertian(texture* _albedo):albedo(_albedo){}
	texture* albedo;
	virtual bool scatter(const ray& r_in, const hit_record & rec,
		Scatter_Record& srec)const override ;
	
	float scattering_pdf(const ray&ray_in, const hit_record&rec, const ray&scattered)override;
};


