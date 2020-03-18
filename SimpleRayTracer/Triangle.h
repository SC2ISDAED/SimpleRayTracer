#pragma once
#include "hitable.h"
#include "ToolsFunction.h"
class material;
class triangle:public hitable
{
public:
	vec3 points[3];
	vec3 normal;
	material * tx;
	triangle(){}
	triangle(vec3 _point1, vec3 _point2, vec3 _point3,material *_tex):tx(_tex)
	{
		points[0] = _point1;
		points[1] = _point2;
		points[2] = _point3;
		normal = ConstructNormal(_point1, _point2, _point3);
	}
	virtual bool hit(const ray&r, float t_min, float t_max, hit_record &rec)const override;
	virtual bool bounding_box(float t0, float t1, AABB& box)const override;
};