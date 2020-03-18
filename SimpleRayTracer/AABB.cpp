#include "AABB.h"
AABB surrounding_box(AABB box0, AABB box1)

{
	vec3 small(ffmin(box0._min.x(), box1._min.x()),
		ffmin(box0._min.y(), box1._min.y()),
		ffmin(box0._min.z(), box1._min.z()));
	vec3 big(ffmax(box0._max.x(), box1._max.x()),
		ffmax(box0._max.y(), box1._max.y()),
		ffmax(box0._max.z(), box1._max.z()));
	return AABB(small, big);
}