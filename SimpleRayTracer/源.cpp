#pragma once
#include <iostream>
#include "fstream"
#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "hitable_list.h"
#include "sphere.h"
#include "float.h"
#include "Camera.h"
#include "random"
#include "ToolsFunction.h"
#include "Math.h"
#include "Material.h"
#include "Lambertian.h"
#include "Material.h"
#include "metal.h"
#include "Dielectrics.h"
#include "MovingSphere.h"
#include "BVH_Node.h"
#include "constant_texture.h"
#include "checker_texture.h"
#include "noise_texture.h"
#include "image_texture.h"
#include "XY_Rect.h"
#include "diffuse_Light.h"
#include "Flip_Normals.h"
#include "box.h"
#include "translate.h"
#include "Constant_Medium.h"
#include "pdf.h"
#include "Triangle.h"
#include "ObjModel.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define  MAXDEPTH 1

vec3 color(const ray &r,hitable *light_shape,hitable * world,int depth)
{
	hit_record hrec;
	
	if (world->hit(r,0.001, MAX_FLOAT,hrec))
	{
		Scatter_Record srec;
		vec3 emitted = hrec.mat_ptr->emitted(r, hrec,hrec.u, hrec.v, hrec.p);

		if (depth< MAXDEPTH && hrec.mat_ptr->scatter(r,hrec, srec))
		{
			if (srec.is_specular)
			{
				return srec.attenuation*color(srec.specular_ray, light_shape, world, depth + 1);
			}
			else
			{
				hitable_pdf pLight(light_shape, hrec.p);
				mixture_pdf p(&pLight, srec.pdf_ptr);
				ray scattered = ray(hrec.p, p.generate(), r.m_time);
				float pdf_val = p.value(scattered.direction);
				delete srec.pdf_ptr;
				return emitted + srec.attenuation*hrec.mat_ptr->scattering_pdf(r, hrec, scattered)
					*color(scattered, light_shape, world, depth + 1) / pdf_val;
			}
		
		}
		else
		{
			return emitted;
		}
	}
	else
	{
		return vec3(0, 0, 0);
	}

}
hitable * random_scene()
{
	int n = 500;
	hitable **list = new hitable *[n + 1];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, 
		new Lambertian(new checker_texture(new constant_texture(vec3(0.5, 0.5, 0.5)), new constant_texture(vec3(0.0, 0.0, 0.0)))));
	int i = 1;
	for (int a=-10;a<10;a++)
	{
		for (int b=-10;b<10;b++)
		{
			float chose_mat = drand48();
			vec3 center(a +  drand48()*0.9, 0.2, b + drand48()*0.9);
			if ((center-vec3(4,0.2,0)).length()>0.9)
			{
				if (chose_mat<0.8)
				{
					list[i++] = new moving_sphere(center, center+vec3(0.0,1.0,0.0),0.0,1.0, 0.2,
						new Lambertian(new constant_texture(vec3(drand48(), drand48(), drand48()))));
				}
				else if (chose_mat < 0.85)
				{
					list[i++] = new sphere(center, 0.2, new Metal(vec3((drand48()+1)*0.5f, (drand48() + 1)*0.5f, (drand48() + 1)*0.5f), drand48()*0.5));
				}
				else if (chose_mat<0.95)
				{
					list[i++] = new sphere(center, 0.5, new Lambertian(new noise_texture(1.0)));
				}
				else
				{
					list[i++] = new sphere(center, 0.2, new Dielectrics(1.5, vec3(drand48(), drand48(), drand48())));
				}
			}
		}
	}
	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new Dielectrics(1.5,vec3(1.0, 1.0, 1.0)));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new Lambertian(new constant_texture(vec3(0.5, 0.5, 0.5))));
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new Metal(vec3(0.7, 0.6, 0.5),0.0));

	return new BVH_Node(list, i,0,1);
}

hitable * two_spheres()
{
	texture * checker = new checker_texture(new constant_texture(vec3(0.5, 0.5, 0.5)), new constant_texture(vec3(0.0, 0.0, 0.0)));
	int nx, ny, nn;
	unsigned char * tex_data1 = stbi_load("f.jpg", &nx, &ny, &nn, 0);
	material * mat1 = new Lambertian(new image_texture(tex_data1,nx,ny));
	unsigned char * tex_data2 = stbi_load("earth.jpg", &nx, &ny, &nn, 0);
	material * mat2 = new Lambertian(new image_texture(tex_data2, nx, ny));
	unsigned char * tex_data3 = stbi_load("jin.jpg", &nx, &ny, &nn, 0);
	material * mat3 = new Lambertian(new image_texture(tex_data3, nx, ny));
	unsigned char * tex_data4 = stbi_load("mo.jpg", &nx, &ny, &nn, 0);
	material * mat4 = new Lambertian(new image_texture(tex_data4, nx, ny));
	unsigned char * tex_data5 = stbi_load("mu.jpg", &nx, &ny, &nn, 0);
	material * mat5 = new Lambertian(new image_texture(tex_data5, nx, ny));
	int n = 50;
	hitable **list = new hitable *[n + 1];
	list[0] = new sphere(vec3(0, 0, 0),1, mat2);



//	list[1] = new sphere(vec3(0, 10, 0), 10, new Lambertian(new noise_texture(1.0)));
	return new BVH_Node(list, 1, 0, 1);
}

hitable * simple_light()
{
	texture * pertext = new noise_texture(4);
	hitable **list = new hitable *[4];
	list[0] = new sphere(vec3(0, -1000, 0), 1000.0, new Lambertian(pertext));
	list[1] = new XZ_Rect(0, 10, 0, 10, 1, new Diffuse_Light(new constant_texture(vec3(1, 1, 1))));
//	list[1] = new YZ_Rect(0,10, 0, 10, -2, new Diffuse_Light(new constant_texture(vec3(1, 1, 1))));
//	list[1] = new XY_Rect(0, 10, 0, 10, -2, new Diffuse_Light(new constant_texture(vec3(1,1,1))));
	return new BVH_Node(list, 2, 0, 1);
}
hitable * cornell_box()
{
	hitable ** list = new hitable *[8];
	material *red = new Lambertian(new constant_texture(vec3(0.65, 0.05, 0.05)));
	material *white = new Lambertian(new constant_texture(vec3(0.73, 0.73, 0.73)));
	material *green = new Lambertian(new constant_texture(vec3(0.12, 0.45, 0.15)));
	material *Light = new Diffuse_Light(new constant_texture(vec3(4, 4, 4)));
	int i = 0;
// 	list[i++] = new flip_normals(new YZ_Rect(0, 555, 0, 555, 555, green));
// 	list[i++] = new YZ_Rect(0, 555, 0, 555, 0, red);
// 	list[i++] = new flip_normals(new XZ_Rect(213, 343, 227, 332, 554, Light));
// 
// 	list[i++] = new flip_normals(new XZ_Rect(0, 555, 0, 555, 555, white));
// 
// 	list[i++] = new XZ_Rect(0, 555, 0, 555, 0, white);
// 	list[i++] = new flip_normals(new XY_Rect(0, 555, 0, 555, 555, white));
	hitable *b1 =new translate(new rotate_y( new Box(vec3(0, 0, 0), vec3(165, 165, 165), white),-18),vec3(130,0,65));
	hitable *b2 =new translate(new rotate_y(new Box(vec3(0, 0, 0), vec3(165, 330, 165), white),15),vec3(265,0,295));
	
	material * aluminum = new Dielectrics( 1.5f, vec3(0.8, 0.85, 0.88));


//	list[i++] = b1;
/*	list[i++]= new sphere(vec3(190, 90, 190), 90, aluminum);*/
// 	list[i++] = new translate(new rotate_y(
// 		new Box(vec3(0, 0, 0), vec3(165, 330, 165), white), 15), vec3(265, 0, 295));
	
//	list[i++] = new triangle(vec3(0, 0, 0), vec3(0, 10, 0), vec3(10, 0, 0), Light);
	list[i++] = new OBJModel("Model/car.txt",white);
	list[i++] =new XY_Rect(-10, 10, -10, 10, -10, Light);
/*	list[i++] =new  rotate_y( new Box(vec3(0, 0, 0), vec3(5, 5, 5), white),15);*/
	return new hitable_list(list, i);
}
hitable *finalSence()
{
	int nb = 20;
	hitable **list = new hitable*[30];
	hitable **boxlist = new hitable*[10000];
	hitable **boxlist2 = new hitable*[10000];

	material * white = new Lambertian(new constant_texture(vec3(0.73,0.73,0.73)));
	material * ground = new Lambertian(new constant_texture(vec3(0.48, 0.83, 0.53)));

	int b = 0;
	for (int i=0;i<nb;i++)
	{
		for (int j=0;j<nb;j++)
		{
			float w = 100;
			float x0 = -1000 + i * w;
			float z0 = -1000 + j * w;
			float y0 = 0;
			float x1 = x0 + w;
			float y1 = 100 * (drand48() + 0.01);
			float z1 = z0 + w;
			boxlist[b++] = new Box(vec3(x0,y0,z0), vec3(x1, y1, z1),ground);
		}
	}
	int l = 0;
	list[l++] = new BVH_Node(boxlist, b, 0, 1);
	material *light = new Diffuse_Light(new constant_texture(vec3(4, 4, 4)));
	list[l++] = new XZ_Rect(123, 423, 147, 412, 554, light);
	vec3 center(400, 400, 200);
	list[l++] = new moving_sphere(center, center + vec3(30, 0, 0), 0, 1, 50,
		new Lambertian(new constant_texture(vec3(0.7, 0.3, 0.1))));
	list[l++] = new sphere(vec3(260, 150, 45), 50, new Dielectrics(1.5,vec3(1.0,1.0,1.0)));
	list[l++] = new sphere(vec3(0, 150, 145), 50, new Metal(vec3(0.8, 0.8, 0.9), 10.0));

	hitable * boundary = new sphere(vec3(360, 150, 145), 70, new Dielectrics(1.5, vec3(1.0, 1.0, 1.0)));
	list[l++] = boundary;
	list[l++] = new constant_medium(boundary, 0.2, new constant_texture(vec3(0.2, 0.4, 0.9)));

	boundary = new sphere(vec3(0, 0, 0), 5000, new Dielectrics(1.5, vec3(1.0, 1.0, 1.0)));

	list[l++] = new constant_medium(boundary, 0.0001, new constant_texture(vec3(1.0, 1.0, 1.0)));
	int nx, ny, nn;
	unsigned char * tex_data = stbi_load("earth.jpg", &nx, &ny, &nn, 0);
	material * mat = new Lambertian(new image_texture(tex_data, nx, ny));
	list[l++] = new sphere(vec3(400, 200, 400), 100, mat);
	texture * pertext = new noise_texture(0.1);
	list[l++] = new sphere(vec3(220, 280, 300), 80, new Lambertian(pertext));
	int ns = 1000;
	for (int j=0;j<ns;j++)
	{
		boxlist2[j] = new sphere(vec3(drand48() * 165, drand48() * 165, drand48() * 165),10,white);
	}
	list[l++] = new translate(new rotate_y(new BVH_Node(boxlist2,ns, 0, 1.0), 15), vec3(-100, 270, 395));

	return new hitable_list(list, l);
}
int main()
{
	std::ofstream file("Result.ppm");

	int nx = 500;
	int ny = 500;
	int ns = 100;
// 	vec3 lookfrom(278, 278, -800);
// 	vec3 lookat(278, 278, 0);

	vec3 lookfrom(0, 0, -100);
	vec3 lookat(0, 0, 0);

	float dist_to_focus = 10;
	float aperture = 0.0;
	Camera cam(lookfrom, lookat,vec3(0,1,0),40,float(nx)/ float(ny), aperture, dist_to_focus,0.0f,1.0f);

	hitable *list[5];
	hitable *world = cornell_box();
	file << "P3\n" << nx << " " << ny << "\n255\n";

	hitable * light_shape = new  XY_Rect(-10, 10, -10, 10, -10, 0);
	hitable * glass_sphere = new sphere(vec3(190, 90, 190), 90, 0);
	hitable *a[2];
	a[0] = light_shape;
	a[1] = glass_sphere;
	hitable_list hlist(a, 2);
	
	for (int j=ny-1;j>=0;j--)
	{
		for (int i=0;i<nx;i++)
		{
			vec3 col(0, 0, 0);

			for (int s=0;s<ns;s++)
			{
				float u = float(i+ drand48()) / float(nx);
				float v = float(j+ drand48()) / float(ny);
				ray r = cam.get_ray(u, v);
				 col += de_nan(color(r, &hlist,world, 0)) ;
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			file << ir << " " << ig << " " << ib << "\n";
		}
	}

	file.close();
}

