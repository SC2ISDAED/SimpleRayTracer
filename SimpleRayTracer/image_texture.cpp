#include "image_texture.h"
#include "vec3.h"
vec3 image_texture::value(float u, float v, const vec3& p)
{
	int i = (u)*nx;
	int j = (1 - v)*ny - 0.001;
	if (i<0)
	{
		i = 0;
	}
	if (j<0)
	{
		j = 0;
	}
	if (i>nx-1)
	{
		i = nx - 1;
	}
	if (j>ny-1)
	{
		j = ny - 1;
	}
	float ir = int(data[3*i+3*nx*j])/255.0;
	float ig = int(data[3 * i + 3 * nx*j+1]) / 255.0;
	float ib = int(data[3 * i + 3 * nx*j+2]) / 255.0;

	return vec3(ir, ig, ib);
}
