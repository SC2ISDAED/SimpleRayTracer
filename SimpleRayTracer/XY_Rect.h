#pragma once
#include "hitable.h"
#include "AABB.h"
class XY_Rect :public hitable
{
public:
	float x0, x1, y0, y1, k;
	material *mp;
	XY_Rect(){}
	XY_Rect(float _x0, float _x1,
		float _y0, float _y1,
		float _k, material *mat):
		x0(_x0),x1(_x1),y0(_y0),y1(_y1),k(_k),mp(mat){}
	virtual bool hit(const ray&r, float t_min,
		float t_max, hit_record &rec)const override;
	virtual bool bounding_box(float t0, float t1, AABB& box)const
	{
		box = AABB(vec3(x0, y0, k - 0.0001), vec3(x1, y1, k + 0.0001));
		return true;
	}
	virtual float pdf_value(const vec3& o, const vec3 &v)const override;
	virtual vec3 random(const vec3& o)const override;
};

class XZ_Rect :public hitable
{
public:
	float x0, x1, z0, z1, k;
	material *mp;
	XZ_Rect() {}
	XZ_Rect(float _x0, float _x1,
		float _z0, float _z1,
		float _k, material *mat) :
		x0(_x0), x1(_x1), z0(z0), z1(_z1), k(_k), mp(mat) {}
	virtual bool hit(const ray&r, float t_min,
		float t_max, hit_record &rec)const override;
	virtual bool bounding_box(float t0, float t1, AABB& box)const
	{
		box = AABB(vec3(x0,k-0.0001 , z0), vec3(x1, k+0.0001, z1));
		return true;
	}
	virtual float pdf_value(const vec3& o, const vec3 &v)const override;
	virtual vec3 random(const vec3& o)const override;
};

class YZ_Rect :public hitable
{
public:
	float y0, y1, z0, z1, k;
	material *mp;
	YZ_Rect() {}
	YZ_Rect(float _y0, float _y1,
		float _z0, float _z1,
		float _k, material *mat) :
		y0(_y0), y1(_y1), z0(z0), z1(_z1), k(_k), mp(mat) {}
	virtual bool hit(const ray&r, float t_min,
		float t_max, hit_record &rec)const override;
	virtual bool bounding_box(float t0, float t1, AABB& box)const
	{
		box = AABB(vec3(k - 0.0001, y0, z0), vec3(k + 0.0001,y1, z1));
		return true;
	}
	virtual float pdf_value(const vec3& o, const vec3 &v)const override;
	virtual vec3 random(const vec3& o)const override;
};