#pragma once
#include "texture.h"
#include "vec3.h"
#include "math.h"
class checker_texture :public texture
{
public:
	texture *odd;
	texture *even;
	checker_texture(){}
	checker_texture(texture * t0,texture * t1)
	:odd(t0),even(t1){}
	virtual vec3 value(float u, float v, const vec3&p) override
	{
		float sines = sin(10 * p.x())*sin(10 * p.y())*sin(10 * p.z());
		if (sines<0)
		{
			return odd->value(u, v, p);
		}
		else
		{
			return even->value(u, v, p);
		}
	}
};