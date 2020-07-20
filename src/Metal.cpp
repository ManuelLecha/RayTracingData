//
// Created by Manuel Lecha Sánchez on 16/03/2020.
//
#define NUMBER_OF_RAYS_SCATTER 3

#include "Metal.h"

Metal::Metal(const vec3 &color) {
    this->specular = color;
}

Metal::Metal(const vec3 &a, const vec3 &d, const vec3 &s, float sh, vec3 transparency) :
        Material(a, d, s, sh, transparency) {
}

Metal::Metal(const vec3 &a, const vec3 &d, const vec3 &s, float sh, vec3 transparency, float fuzziness): Material(a, d, s, sh, transparency){
    this->fuzziness = fuzziness;
}

Metal::~Metal() {
}

bool
Metal::scatter(const Ray &r_in, const IntersectionInfo &rec, std::vector<vec3> &color, std::vector<Ray> &r_out) const {
    for(int i=0; i<NUMBER_OF_RAYS_SCATTER; i++) {
        vec3 specularVec = reflect(normalize(r_in.direction), rec.normal);
        vec3 diffuseVec = this->RandomInSphere();

        vec3 vecReflected = (1-fuzziness)*specularVec + fuzziness*diffuseVec;
        vec3 attColor = (1-fuzziness)*specular + fuzziness*diffuse;
        r_out.push_back(Ray(rec.p, vecReflected));
        color.push_back(attColor);
    }
    return true;
}
