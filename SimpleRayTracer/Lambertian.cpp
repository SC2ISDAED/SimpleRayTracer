#include "Lambertian.h"
#include "ONB.h"
bool Lambertian::scatter(const ray& r_in, const hit_record & rec,
	Scatter_Record& srec) const
{
	srec.is_specular = false;
	srec.attenuation = albedo->value(rec.u, rec.v, rec.p);

	srec.pdf_ptr = new cosine_pdf(rec.normal);

	return true;

}

float Lambertian::scattering_pdf(const ray&ray_in, const hit_record&rec, const ray&scattered)
{
	float cosine = dot(rec.normal, make_unit_vector(scattered.direction));
	if (cosine < 0)
	{
		cosine = 0;
	}
	return cosine / M_PI;
}
