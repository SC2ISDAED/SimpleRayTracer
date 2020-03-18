#pragma once
#include "vec3.h"
#include "ONB.h"
#include "ToolsFunction.h"

class pdf
{
public:
	virtual float value(const vec3& direction) const = 0;
	virtual vec3 generate()const = 0;
};

class cosine_pdf :public pdf
{
public:
	ONB uvw;
	cosine_pdf(const vec3&w)
	{
		uvw.build_from_w(w);
	}
	virtual float value(const vec3& direction)const override
	{
		float cosine = dot(make_unit_vector(direction), uvw.w());
		if (cosine > 0)
		{
			return cosine / M_PI;
		}
		else
		{
			return 0;
		}
	}
	virtual vec3 generate()const
	{
		return uvw.Local(random_cosine_direction());
	}
};

class hitable_pdf :public pdf
{
public:
	vec3 o;
	hitable * ptr;
	hitable_pdf(hitable *p,const vec3& origin):ptr(p),o(origin){}

	virtual float value(const vec3& direction)const override
	{
		return ptr->pdf_value(o, direction);
	}
	virtual vec3 generate()const
	{
		return ptr->random(o);
	}
};

class mixture_pdf :public pdf
{
public:
	pdf *p[2];
	mixture_pdf(pdf *p0, pdf *p1) { p[0] = p0; p[1] = p1; }

	virtual float value(const vec3 &dirction)const override
	{
		return 0.5*p[0]->value(dirction) + 0.5 *p[1]->value(dirction);
	}

	virtual vec3 generate()const override
	{
		if (drand48()<0.5f)
		{
			return p[0]->generate();
		}
		else
		{
			return p[1]->generate();
		}
	}
};