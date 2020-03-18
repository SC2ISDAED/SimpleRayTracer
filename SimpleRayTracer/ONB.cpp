#include "ONB.h"

void ONB::build_from_w(const vec3 &n)
{
	axis[2] = make_unit_vector(n);
	vec3 a;
	if (fabs(w().x())>0.9)
	{
		a = vec3(0, 1, 0);
	}
	else
	{
		a = vec3(1, 0, 0);
	}
	axis[1] = make_unit_vector(cross(w(), a));
	axis[0] = cross(w(), v());
	
}
