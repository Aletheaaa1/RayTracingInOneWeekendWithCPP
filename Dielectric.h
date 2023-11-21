#pragma once
#include "Material.h"

class Dielectric : public Material
{
public:
	Dielectric() = default;
	Dielectric(double ir);
	bool Scatter(const Ray& r_in, HitRecord& rec, glm::dvec3& attenuation, Ray& scattered) const override;

public:
	double ir;
};

inline Dielectric::Dielectric(double ir) : ir(ir)
{
}

inline bool Dielectric::Scatter(const Ray& r_in, HitRecord& rec, glm::dvec3& attenuation, Ray& scattered) const
{
	attenuation = glm::dvec3(1.0, 1.0, 1.0);
	double refraction_ratio;
	glm::dvec3 unit_direction = glm::normalize(r_in.dir);

	glm::dvec3 normal;
	if (dot(r_in.dir, rec.normal) > 0)
	{
		refraction_ratio = ir;
		normal = -rec.normal;
		//rec.normal = -rec.normal;
	}
	else
	{
		refraction_ratio = 1.0 / ir;
		normal = rec.normal;
	}

	double cos_theta = abs(dot(unit_direction, normal));
	double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

	bool can_refract = refraction_ratio * sin_theta < 1.0;
	glm::dvec3 direction;

	if (can_refract)
	{
		glm::dvec3 refracted_h = refraction_ratio * (unit_direction + normal * cos_theta);
		glm::dvec3 refracted_v = -normal * sqrt(1.0 - dot(refracted_h, refracted_h));
		direction = refracted_h + refracted_v;
		scattered = Ray(rec.p, direction);
	}
	else
	{
		if (glm::dot(r_in.dir, normal) < 0)
		{
			direction = reflect(r_in.dir, normal);
			scattered = Ray(rec.p, direction);
		}
	}

	return true;
}
