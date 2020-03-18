#pragma once
#include "hitable.h"
#include "texture.h"
#include "pdf.h"
struct Scatter_Record
{
	ray specular_ray;
	bool is_specular;
	vec3 attenuation;
	pdf *pdf_ptr;
};
class material
{
public:
	texture * emit;
	virtual bool scatter(const ray& r_in, const hit_record & rec,
		Scatter_Record& srec)const
	{
		return false;
	};
	virtual float scattering_pdf(const ray&ray_in,const hit_record&rec,const ray&scattered)
	{
		return false;
	}
	virtual vec3 emitted(const ray& r_in,const hit_record& rec,float u, float v, const vec3& p)const
	{
		
		return vec3(0, 0, 0);
	}

};