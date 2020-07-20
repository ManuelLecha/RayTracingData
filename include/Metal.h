//
// Created by Manuel Lecha Sánchez on 16/03/2020.
//

#ifndef METAL_H
#define METAL_H


#include "Material.h"

#define DEFAULT_FUZZINESS 0.1

class Metal : public Material {

public:
    float fuzziness = DEFAULT_FUZZINESS;

    Metal(const vec3 &color);

    Metal(const vec3 &a, const vec3 &d, const vec3 &s, float sh, vec3 transparency);

    Metal(const vec3 &a, const vec3 &d, const vec3 &s, float sh, vec3 transparency, float fuzziness);

    virtual ~Metal();

    bool scatter(const Ray &r_in, const IntersectionInfo &rec, std::vector<vec3> &color,
                 std::vector<Ray> &r_out) const override;
};


#endif //METAL_H
