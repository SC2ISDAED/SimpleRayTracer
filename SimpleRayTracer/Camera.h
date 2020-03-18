#pragma once

#include "ray.h"
#include "ToolsFunction.h"
class Camera
{
public:
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 origin;
	float lens_radius;
	vec3 u, v, w;
	float time0, time1;

	Camera(vec3 lookfrom,vec3 lookat,vec3 vup,float vfov,float aspect,
		float aperture,float foucus_dis,float t0,float t1)
	{
		time0 = t0;
		time1 = t1;
		lens_radius = aperture / 2;
		float theta = vfov * M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;

		origin = lookfrom;
		w = make_unit_vector(lookfrom - lookat);
		u = make_unit_vector(cross(vup, w));
		v = cross(w, u);

		lower_left_corner = origin - half_width * u* foucus_dis - half_height * v* foucus_dis - w * foucus_dis;

		horizontal =2 * half_width * u * foucus_dis;
		vertical = 2 * half_height * v * foucus_dis;

	}
	ray get_ray(float s, float t)
	{
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();
		float time = time0 + drand48()*(time1 - time0);
		return ray(origin, lower_left_corner + s * horizontal + t * vertical - origin-offset, time);
	}
	
};
