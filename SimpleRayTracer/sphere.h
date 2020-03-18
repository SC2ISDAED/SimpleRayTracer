#pragma once
#include "hitable.h"

class sphere :public hitable
{
	public:
		sphere(){}
		sphere(vec3 _center, float _radius, material *_materialType):center(_center),radius(_radius),materialType(_materialType)
		{}
		material *materialType;
		vec3 center;
		float radius;

		virtual bool hit(const ray&r, float t_min, float t_max, hit_record &rec)const override;
		bool bounding_box(float t0, float t1, AABB& box)const override;
		float pdf_value(const vec3& o, const vec3 &v)const override;
		vec3 random(const vec3& o)const override;
};


