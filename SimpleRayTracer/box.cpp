#include "box.h"
#include "AABB.h"
#include "XY_Rect.h"
#include "hitable_list.h"
#include "Flip_Normals.h"
Box::Box(const vec3&p0, const vec3& p1, material *ptr)
{
	pmin = p0;
	pmax = p1;
	hitable **list = new hitable*[6];
	list[0] = new XY_Rect(p0.x(),p1.x(), p0.y(), p1.y(), p1.z(), ptr);
	list[1] = new flip_normals(new XY_Rect(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));
	list[2] = new XZ_Rect(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr);
	list[3] = new flip_normals(new XZ_Rect(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));
	list[4] = new YZ_Rect(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr);
	list[5] = new flip_normals(new YZ_Rect(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
	list_ptr = new hitable_list(list, 6);
}

bool Box::hit(const ray&r, float t_min, float t_max, hit_record &rec) const
{
	return list_ptr->hit(r, t_min, t_max, rec);
}

bool Box::bounding_box(float t0, float t1, AABB& box) const
{
	box = AABB(pmin, pmax);
	return true;
}

