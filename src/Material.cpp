#include "Material.h"


Material::Material() :
        diffuse(1.0f) {
    transparency = vec3(0, 0, 0.0);
    transparencyComplementary = vec3(1.0, 1.0, 1.0);
}

Material::~Material() {
}


Material::Material(vec3 a, vec3 d, vec3 s, float sh, vec3 transparency) {
    diffuse = d;
    ambient = a;
    specular = s;
    shininess = sh;
    this->transparency = transparency;
    this->transparencyComplementary = vec3(1.0, 1.0, 1.0) - transparency;
}

vec3 Material::getDiffuse(vec2 point) const {
    return this->diffuse;
}

bool Material::scatter(const Ray &r_in, const IntersectionInfo &rec, std::vector<vec3> &colors,
                       std::vector<Ray> &r_out) const {
    return false;
}

vec3 Material::RandomInSphere() const {
    vec3 p;
    do {
        p = 2.0f * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while (glm::length(p) >= 1.0f);
    return p;
}