#include "MovingSphere.h"
#include "ToolsFunction.h"
#include "AABB.h"
bool moving_sphere::hit(const ray&r, float t_min, float t_max, hit_record &rec) const
{
	vec3 oc = r.origin - center(r.m_time);
	float a = dot(r.direction, r.direction);
	float b = dot(oc, r.direction);
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0)
	{
		float temp = (-b - sqrt(b*b - a * c)) / a;
		if (temp<t_max&&temp>t_min)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center(r.m_time)) / radius;
			rec.mat_ptr = mat_ptr;
			get_sphere_uv((rec.p - center(r.m_time)) / radius, rec.u, rec.v);
			return true;
		}
		temp = (-b + sqrt(b*b - a * c)) / a;
		if (temp<t_max&&temp>t_min)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center(r.m_time)) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}

bool moving_sphere::bounding_box(float t0, float t1, AABB& box) const
{

	AABB boxOne(center(t0) - vec3(radius, radius, radius), center(t0) + vec3(radius, radius, radius));
	AABB boxTwo(center(t1) - vec3(radius, radius, radius), center(t1) + vec3(radius, radius, radius));
	box = surrounding_box(boxOne, boxTwo);
	return true;
}
