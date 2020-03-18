#include "ObjModel.h"
#include "fstream"
#include "string"
#include "AABB.h"
#include "ToolsFunction.h"
#include "vec3.h"
OBJModel::OBJModel(std::string path, material *_tex):tex(_tex)
{
	std::ifstream fin("Model/skull.txt");

	unsigned int vcount = 0;
	unsigned int tcount = 0;
	std::string ignore;

	fin >> ignore >> vcount;
	fin >> ignore >> tcount;
	fin >> ignore >> ignore >> ignore >> ignore;

	vertices.resize(vcount);
	normals.resize(vcount);
	for (unsigned int i = 0; i < vcount; ++i)
	{
		fin >> vertices[i].e[0] >> vertices[i].e[1] >> vertices[i].e[2];
		fin >> normals[i].e[0] >> normals[i].e[1] >> normals[i].e[2];
		vertices[i] *= 10;
	}

	fin >> ignore;
	fin >> ignore;
	fin >> ignore;

	indexs.resize(3 * tcount);
	for (unsigned int i = 0; i < tcount; ++i)
	{
		fin >> indexs[i * 3 + 0] >> indexs[i * 3 + 1] >> indexs[i * 3 + 2];
	}

	fin.close();

}

bool OBJModel::hit(const ray&r, float t_min, float t_max, hit_record &rec) const
{
	for (int i=0;i<vertices.size();i++)
	{
		vec3 hit_point;
		bool ishit = IntersetTriangle(r, vertices[indexs[i*3]], vertices[indexs[i*3+1]], 
			vertices[indexs[i*3+2]], hit_point);
		if (ishit)
		{
			rec.normal = normals[i];
			rec.p = hit_point;
			rec.mat_ptr = tex;
			//u,v Î´Ëã
			rec.t = ((hit_point - r.origin) / r.direction).length();
			return true;
		}
	}
	return false;
}

bool OBJModel::bounding_box(float t0, float t1, AABB& box) const
{
	vec3 max, min;
	for (auto vc :vertices)
	{
		if (vc.x()>max.x())
		{
			max.e[0] = vc.x();
		}
		if (vc.y() > max.y())
		{
			max.e[1] = vc.y();
		}
		if (vc.z() > max.z())
		{
			max.e[2] = vc.z();
		}

		if (vc.x() < max.x())
		{
			min.e[0] = vc.x();
		}
		if (vc.y() < max.y())
		{
			min.e[1] = vc.y();
		}
		if (vc.z()  <max.z())
		{
			min.e[2] = vc.z();
		}
	}

	box= AABB(min, max);
	return true;
}

