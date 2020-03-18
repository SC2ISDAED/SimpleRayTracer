#include "sphere.h"
#include "AABB.h"
#include "math.h"
#include "ToolsFunction.h"
#include "ONB.h"
bool sphere::hit(const ray&r, float t_min, float t_max, hit_record &rec)const
{
	vec3 oc = r.Getorigin() - center;
	float a = dot(r.GetDirection(), r.GetDirection());
	float b = dot(oc, r.GetDirection());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0)
	{
		float temp = (-b - sqrt(b*b - a * c)) / a;
	
	

		if (temp<t_max&&temp>t_min)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = materialType;
			get_sphere_uv((rec.p - center) / radius, rec.u, rec.v);
			return true;
		}
		temp = (-b + sqrt(b*b - a * c)) / a;
		if (temp<t_max&&temp>t_min)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = materialType;
			get_sphere_uv((rec.p - center) / radius, rec.u, rec.v);
			return true;
		}
	}
	return false;
}

bool sphere::bounding_box(float t0, float t1, AABB& box) const
{
	box = AABB(center - vec3(radius, radius, radius), center + vec3(radius, radius, radius));
	return true;
}

float sphere::pdf_value(const vec3& o, const vec3 &v) const
{
	hit_record rec;
	if (this->hit(ray(o,v),0.001,FLT_MAX,rec))
	{
		float cos_theata_max = sqrt(1 - radius * radius / (center - o).squared_length());
		float solid_angle = 2 * M_PI *(1 - cos_theata_max);
		return 1 / solid_angle;
	}
	else
	{
		return 0;
	}
}

vec3 sphere::random(const vec3& o) const
{
	vec3 direction = center - o;
	float distance_squared = direction.squared_length();

	ONB uvw;
	uvw.build_from_w(direction);

	return uvw.Local(random_to_sphere(radius,distance_squared));
}

