#pragma once
#include "vec3.h"


class ray
{
public:
	vec3 origin;
	vec3 direction;
	float m_time;
	ray(){}
	ray(const vec3& _origin, const vec3 & _direction,float ti=0.0)
	{
		origin = _origin;
		direction = _direction;
		m_time = ti;
	};
	vec3 Getorigin()const { return origin; }
	vec3 GetDirection()const { return direction; }

	vec3 point_at_parameter(float t) const { return origin +  direction*t ; }

};