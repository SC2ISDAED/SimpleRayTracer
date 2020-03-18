#pragma once
#include "vec3.h"
#include "ray.h"
inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

class AABB
{
public:
	vec3 _min;
	vec3 _max;
	AABB(){}
	AABB(const vec3& a, const vec3&b)
	{
		_min = a;
		_max = b;
	}

	bool hit(const ray&r, float t_min, float t_max)const
	{
		for (int a=0;a<3;a++)
		{
			float invD = 1.0f / r.direction[a];
			float t0 = (_min[a] - r.origin[a])*invD;
			float t1 = (_max[a] - r.origin[a])*invD;
			if (invD<0.0f)
			{
				std::swap(t0, t1);
			}
			t_min = ffmax(t0, t_min);
			t_max = ffmin(t1, t_max);
			if (t_max<=t_min)
			{
				return false;
			}
		}
		return true;
	}
};
AABB surrounding_box(AABB box0, AABB box1);