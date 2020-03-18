#include "Triangle.h"
#include "ray.h"
#include "AABB.h"
#include "Material.h"
bool triangle::hit(const ray&r, float t_min, float t_max, hit_record &rec) const
{
	vec3 hit_point;
	bool ishit = IntersetTriangle(r, points[0], points[1], points[2], hit_point);
	if (ishit)
	{
		rec.normal = normal;
		rec.p = hit_point;
		rec.mat_ptr = tx;
		//u,v Œ¥À„
		rec.t = ((hit_point - r.origin)/r.direction).length();
		return true;
	}
	else
	{
		return false;
	}
}

bool triangle::bounding_box(float t0, float t1, AABB& box) const
{

	box = AABB(points[0], points[1]);
	return true;
}
