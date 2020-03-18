#pragma once
#include "Material.h"
#include "ToolsFunction.h"
class Dielectrics :public material
{
public:
	
	float ref_idx;
	vec3 albedo;
	Dielectrics(float ri,vec3 _albedo) :ref_idx(ri),albedo(_albedo)
	{}
	virtual bool scatter(const ray& r_in, const hit_record & rec,
		Scatter_Record& srec)const override
	{
	
		vec3 reflected = reflect(r_in.GetDirection(), rec.normal);

		srec.attenuation = albedo;
		float ni_over_nt;
		vec3 outward_normal;

		srec.pdf_ptr = 0;
		srec.is_specular = true;

		vec3 refracted;
		float reflect_prob;
		float cosin;
	
		if (dot(r_in.GetDirection(),rec.normal)>0)
		{
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			cosin = ref_idx * dot(r_in.GetDirection(), rec.normal) / r_in.GetDirection().length();
		}
		else
		{
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / ref_idx;
			cosin=-dot(r_in.GetDirection(),rec.normal)/ r_in.GetDirection().length();
		}
		if (refract(r_in.GetDirection(),outward_normal,ni_over_nt,refracted))
		{
			reflect_prob = schlick(cosin, ref_idx);
		}
		else
		{
			reflect_prob = 1.0;
		}
		if (drand48()<reflect_prob)
		{
			srec.specular_ray = ray(rec.p, reflected);
		}
		else
		{
			srec.specular_ray = ray(rec.p, refracted);
		}
	
		return true;
	}
};
