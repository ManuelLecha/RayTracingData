#include "Lambertian.h"
#define NUMBER_OF_RAYS_SCATTER 3

Lambertian::Lambertian(const vec3 &color) : Material() {
    diffuse = color;
}

Lambertian::Lambertian(const vec3 &a, const vec3 &d, const vec3 &s, float sh, vec3 transparency) :
        Material(a, d, s, sh, transparency) {
}

Lambertian::~Lambertian() {
}

bool Lambertian::scatter(const Ray &r_in, const IntersectionInfo &rec, std::vector<vec3> &color,
                         std::vector<Ray> &r_out) const {
    for(int i=0; i < NUMBER_OF_RAYS_SCATTER; i++) {
        vec3 target = rec.p + rec.normal + this->RandomInSphere();
        r_out.push_back(Ray(rec.p, target - rec.p));
        color.push_back(diffuse);
    }
    return true;
}

