//
// Created by eudald on 3/28/20.
//

#include "BaseMaterial.h"

BaseMaterial::BaseMaterial(vec3 color) {
    diffuse = color;
    ambient = color * 0.1f;
}

bool BaseMaterial::scatter(const Ray &r_in, const IntersectionInfo &rec, std::vector<vec3> &colors,
                           std::vector<Ray> &r_out) const {
    return false;
}
