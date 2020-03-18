#pragma once
#include "hitable.h"
#include "AABB.h"
#include "ToolsFunction.h"
class BVH_Node :public hitable
{

public:
	BVH_Node(){}
	BVH_Node(hitable **list,int n,float time0,float time1);
	virtual bool hit(const ray&r, float t_min, float t_max, hit_record &rec)const override;
	virtual bool bounding_box(float t0, float t1, AABB& box)const override;
	hitable *left;
	hitable * right;
	AABB box;
};