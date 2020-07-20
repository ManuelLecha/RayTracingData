#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.h"

class Lambertian : public Material {

public:
    Lambertian(const vec3 &color);

    Lambertian(const vec3 &a, const vec3 &d, const vec3 &s, float sh, vec3 transparency);

    virtual ~Lambertian();

    virtual bool
    scatter(const Ray &r_in, const IntersectionInfo &rec, std::vector<vec3> &color, std::vector<Ray> &r_out) const;
};

#endif // LAMBERTIAN_H
