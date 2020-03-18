#pragma once
#include "vec3.h"
class ONB
{
public:
	vec3 axis[3];
	ONB(){}
	vec3 u()const { return axis[0]; }
	vec3 v()const { return axis[1]; }
	vec3 w()const { return axis[2]; }

	vec3 Local(float a,float b,float c)const 
	{
		return a* u() + b * v() + c * w();
	}
	vec3 Local(const vec3&a) const { return a.x()*u()+ a.y()*v() + a.z()*w(); }

	void build_from_w(const vec3 &n);

};
