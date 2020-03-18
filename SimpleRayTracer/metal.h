#pragma once
#include "ray.h"
#include "Material.h"
#include "ToolsFunction.h"

class Metal :public material
{
public:
	vec3 albedo;
	float roughness=1;
	Metal(const vec3& a,float _roughness):albedo(a),roughness(_roughness){}
	virtual bool scatter(const ray& r_in, const hit_record & rec,
		Scatter_Record& srec)const override
	{

		vec3 reflected = reflect(make_unit_vector(r_in.direction), rec.normal);
		srec.specular_ray = ray(rec.p, reflected + random_in_unit_sphere()*roughness);
		srec.attenuation = albedo;
		srec.is_specular = true;
		srec.pdf_ptr = 0;
		return true;
	}
};
