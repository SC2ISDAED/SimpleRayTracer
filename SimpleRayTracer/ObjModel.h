#pragma once
#include "hitable.h"
#include "vec3.h"
#include "vector"
class  OBJModel :public hitable
{
public:
	material * tex;
	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<int>  indexs;
	OBJModel(std::string path,material *_tex);
	virtual bool hit(const ray&r, float t_min, float t_max, hit_record &rec)const override;
	virtual bool bounding_box(float t0, float t1, AABB& box)const override;
};
