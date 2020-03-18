#pragma once
#include "texture.h"
#include "perlin.h"
class noise_texture :public texture
{
public:
	noise_texture(){}
	noise_texture(float sc):scale(sc){}
	virtual vec3 value(float u, float v, const vec3&p)override
	{
		return vec3(drand48()*0.9, drand48()*0.2, drand48()*0.2)*0.5*(1+sin(scale*p.z()+ 10*noise.trub(p)));
		//return vec3(drand48(), drand48(), drand48());
	}
	perlin noise;
	float scale=1.0;
};