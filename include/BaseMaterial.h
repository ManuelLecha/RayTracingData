//
// Created by eudald on 3/28/20.
//

#ifndef RAYDATA_BASEMATERIAL_H
#define RAYDATA_BASEMATERIAL_H

#include "Material.h"


class BaseMaterial : public Material {
public:
    BaseMaterial(vec3 color);

    virtual bool
    scatter(const Ray &r_in, const IntersectionInfo &rec, std::vector<vec3> &colors, std::vector<Ray> &r_out) const;
};


#endif //RAYDATA_BASEMATERIAL_H
