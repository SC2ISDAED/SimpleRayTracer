#include "XY_Rect.h"
#include "ToolsFunction.h"
bool XY_Rect::hit(const ray&r, float t_min, float t_max, hit_record &rec) const
{
	float t = (k - r.origin.z()) / r.direction.z();
	if (t< t_min ||t>t_max)
	{
		return false;
	}
	float x = r.origin.x() + t * r.direction.x();
	float y = r.origin.y() + t * r.direction.y();

	if (x<x0||x>x1||y<y0||y>y1)
	{
		return false;
	}
	rec.u = (x - x0) / (x1 - x0);
	rec.v = (y - y0) / (y1 - y0);
	rec.t = t;

	rec.mat_ptr = mp;
	rec.p = r.point_at_parameter(t);
	rec.normal = vec3(0, 0, 1);

	return true;
}

float XY_Rect::pdf_value(const vec3& o, const vec3 &v) const
{
	hit_record rec;
	if (this->hit(ray(o, v), 0.01, FLT_MAX, rec))
	{
		float area = (x1 - x0)*(y0 - y1);
		float distance_squared = rec.t*rec.t*v.squared_length();
		float cosine = fabs(dot(v, rec.normal) / v.length());
		return distance_squared / (cosine*area);
	}
	else
		return 0;
}

vec3 XY_Rect::random(const vec3& o) const
{
	vec3 random_point = vec3(x0 + drand48()*(x1 - x0),y0 + drand48()*(y1 - y0), k);
	return random_point - o;
}

bool XZ_Rect::hit(const ray&r, float t_min, float t_max, hit_record &rec) const
{
	float t = (k - r.origin.y()) / r.direction.y();
	if (t< t_min || t>t_max)
	{
		return false;
	}
	float x = r.origin.x() + t * r.direction.x();
	float z = r.origin.z() + t * r.direction.z();

	if (x<x0 || x>x1 || z<z0 || z>z1)
	{
		return false;
	}
	rec.u = (x - x0) / (x1 - x0);
	rec.v = (z - z0) / (z1 - z0);
	rec.t = t;

	rec.mat_ptr = mp;
	rec.p = r.point_at_parameter(t);
	rec.normal = vec3(0, 1, 0);

	return true;
}

float XZ_Rect::pdf_value(const vec3& o, const vec3 &v) const
{
	hit_record rec;
	if (this->hit(ray(o, v), 0.01, FLT_MAX, rec))
	{
		float area = (x1 - x0)*(z1 - z0);
		float distance_squared = rec.t*rec.t*v.squared_length();
		float cosine = fabs(dot(v, rec.normal) / v.length());
		return distance_squared / (cosine*area);
	}
	else
		return 0;
}

vec3 XZ_Rect::random(const vec3& o) const
{
	vec3 random_point = vec3(x0 + drand48()*(x1 - x0), k, z0 + drand48()*(z1-z0));
	return random_point - o;
}

bool YZ_Rect::hit(const ray&r, float t_min, float t_max, hit_record &rec) const
{
	float t = (k - r.origin.x()) / r.direction.x();
	if (t< t_min || t>t_max)
	{
		return false;
	}
	float y = r.origin.y() + t * r.direction.y();
	float z = r.origin.z() + t * r.direction.z();

	if (y<y0 || y>y1 || z<z0 || z>z1)
	{
		return false;
	}
	rec.u = (y - y0) / (y1 - y0);
	rec.v = (z - z0) / (z1 - z0);
	rec.t = t;

	rec.mat_ptr = mp;
	rec.p = r.point_at_parameter(t);
	rec.normal = vec3(1, 0, 0);

	return true;
}

float YZ_Rect::pdf_value(const vec3& o, const vec3 &v) const
{
	hit_record rec;
	if (this->hit(ray(o, v), 0.01, FLT_MAX, rec))
	{
		float area = (y0 - y1)*(z0 - z1);
		float distance_squared = rec.t*rec.t*v.squared_length();
		float cosine = fabs(dot(v, rec.normal) / v.length());
		return distance_squared / (cosine*area);
	}
	else
		return 0;
}

vec3 YZ_Rect::random(const vec3& o) const
{
	vec3 random_point = vec3(k, y0 + drand48()*(y1 - y0), z0 + drand48()*(z1 - z0));
	return random_point - o;
}
