//
// Created by ruben on 29/3/20.
//

#ifndef RAYDATA_TRANSPARENT_H
#define RAYDATA_TRANSPARENT_H


#include "Material.h"

vec3 colorTransparency(vec3 color, float d);

class Transparent : public Material {
public:
    Transparent(const vec3 &color);

    Transparent(const vec3 &a, const vec3 &d, const vec3 &s, float sh, vec3 transparency);

    Transparent(const vec3 &a, const vec3 &d, const vec3 &s, float sh, float idxRefraccio, vec3 transparency);

    virtual ~Transparent() {};

    virtual bool
    scatter(const Ray &r_in, const IntersectionInfo &rec, std::vector<vec3> &color, std::vector<Ray> &r_out) const;

private:
    float idxRefraccio;
};


#endif //RAYDATA_TRANSPARENT_H
