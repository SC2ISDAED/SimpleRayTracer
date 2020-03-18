#pragma once
class vec3;
class texture
{
public:
	virtual vec3 value(float u, float v, const vec3& p) = 0;
};
