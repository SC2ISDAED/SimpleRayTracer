
#include "BVH_Node.h"
#include<stdlib.h>

int box_x_compare(const void * a, const void *b)
{
	AABB box_left, box_right;
	hitable *ah = *(hitable**)a;
	hitable *bh = *(hitable**)b;
	if (!ah->bounding_box(0,0,box_left)||!bh->bounding_box(0,0,box_right))
	{
		std::cerr << "no bounding box in bvh_node consturctor\n";
	}
	if ((box_left._min.x() - box_right._min.x())<0.0)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}
int box_y_compare(const void * a, const void *b)
{
	AABB box_left, box_right;
	hitable *ah = *(hitable**)a;
	hitable *bh = *(hitable**)b;
	if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
	{
		std::cerr << "no bounding box in bvh_node consturctor\n";
	}
	if (box_left._min.y() - box_right._min.y() < 0.0)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}
int box_z_compare(const void * a, const void *b)
{
	AABB box_left, box_right;
	hitable *ah = *(hitable**)a;
	hitable *bh = *(hitable**)b;
	if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
	{
		std::cerr << "no bounding box in bvh_node consturctor\n";
	}
	if (box_left._min.z() - box_right._min.z() < 0.0)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}
BVH_Node::BVH_Node(hitable **list, int n, float time0, float time1)
{
	int axis = int( drand48()*3);
	if (axis==0)
	{
		qsort(list, n, sizeof(hitable *), box_x_compare);
	}
	else if (axis==1)
	{
		qsort(list, n, sizeof(hitable *), box_y_compare);
	}
	else
	{
		qsort(list, n, sizeof(hitable *), box_z_compare);
	}
	if (n==1)
	{
		left = right = list[0];
	}
	else if (n==2)
	{
		left = list[0];
		right = list[1];
	}
	else
	{
		left = new BVH_Node(list, n / 2, time0, time1);
		right = new BVH_Node(list + n / 2, n - n / 2, time0, time1);
	}
	AABB box_left, box_right;

	if (!left->bounding_box(time0, time1, box_left) || !right->bounding_box(time0, time1, box_right))
	{
		//为左右孩子搭建 包围盒，如果是Nan的包围盒输出错误
		std::cerr << "no bounding box in bvh_node consturctor\n";
	}
	//合并左右孩子的包围盒
	box = surrounding_box(box_left, box_right);
}

bool BVH_Node::hit(const ray&r, float t_min, float t_max, hit_record &rec) const
{
	if (box.hit(r,t_min,t_max))
	{
		hit_record left_rec, right_rec;
		bool hit_left = left->hit(r, t_min, t_max, left_rec);
		bool hit_right = right->hit(r, t_min, t_max, right_rec);
		if (hit_left&&hit_right)
		{
			//找到最近那个击中点
			if (left_rec.t < right_rec.t)
			{
				rec = left_rec;
			}
			else
			{
				rec = right_rec;
			}
			return true;
		}
		else if (hit_left)
		{
			rec = left_rec;
			return true;
		}
		else if (hit_right)
		{
			rec = right_rec;
			return true;
		}
		else
			return false;
	}
	else
	{
		return false;
	}
}

bool BVH_Node::bounding_box(float t0, float t1, AABB& b) const
{
	b = box;
	return true;
}
