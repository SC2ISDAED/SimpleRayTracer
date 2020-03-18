#include "Constant_Medium.h"
bool constant_medium::bounding_box(float t0, float t1, AABB& box) const
{
	return boundary->bounding_box(t0, t1, box);
}

bool constant_medium::hit(const ray&r, float t_min, float t_max, hit_record &rec) const
{
	bool db = (drand48() < 0.00001);
	db = false;
	hit_record rec1, rec2;
	//rec1第一个击中点，rec2 为第二个击中点
	if (boundary->hit(r,-FLT_MAX,FLT_MAX,rec1))
	{
		if (boundary->hit(r,rec1.t+0.0001,FLT_MAX,rec2))
		{
			if (db)
			{
				std::cerr << "\nt0 t1" << rec1.t << " " << rec2.t << "\n";
			}
			if (rec1.t<t_min)
			{
				rec1.t = t_min;
			}
			if (rec2.t>t_max)
			{
				rec2.t = t_max;
			}
			if (rec1.t>=rec2.t)
			{
				return false;
			}
			if (rec1.t<0)
			{
				rec1.t = 0;
			}
			float distance_inside_boundary = (rec2.t - rec1.t)*r.direction.length();
			float hit_distance = -(1 / density)*log(drand48());
			if (hit_distance<distance_inside_boundary)
			{
				rec.t = rec1.t + hit_distance / r.direction.length();
				rec.p = r.point_at_parameter(rec.t);
				rec.normal = vec3(1, 0, 0);
				rec.mat_ptr = phase_function;
		
				if (db)
				{
					std::cerr << "hit_distance= " << hit_distance<<"\n";
					std::cerr << "rec.t= " << rec.t << "\n";
					std::cerr << "rec.p= " << rec.p << "\n";
				}
				return true;

			}
		}
	}
	return false;
}

