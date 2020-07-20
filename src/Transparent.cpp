//
// Created by ruben on 29/3/20.
//

#include "Transparent.h"
#include <include/Scene.h>
#include "ColorConversion.h"




Transparent::Transparent(const vec3 &color) {
    this->specular = color;
    this->transparency = vec3(1.0, 1.0, 1.0) - color;
    this->idxRefraccio = 1.000294; //Air idx
}

Transparent::Transparent(const vec3 &a, const vec3 &d, const vec3 &s, float sh, vec3 transparency) :
        Material(a, d, s, sh, transparency) {
    this->idxRefraccio = 1.000294; //Air idx
}

Transparent::Transparent(const vec3 &a, const vec3 &d, const vec3 &s, float sh, float idxRefraccio, vec3 transparency) :
        Material(a, d, s, sh, transparency) {
    this->idxRefraccio = idxRefraccio;

}

bool Transparent::scatter(const Ray &r_in, const IntersectionInfo &rec, std::vector<vec3> &color,
                          std::vector<Ray> &r_out) const {
    ;
    vec3 normal = normalize(rec.normal);
    vec3 incidente = normalize(r_in.direction);
    float cosA = dot(normal, incidente);
    float coef;
    if (cosA > 0) {
        normal = -normal;
        coef = idxRefraccio / float(Scene::AMBIENT_REFRACTION_IDX);
    } else {
        coef = Scene::AMBIENT_REFRACTION_IDX / (float) idxRefraccio;
    }
    vec3 vecRefracted = refract(incidente, normal, coef);
    if (dot(normal, vecRefracted) > 0) {
        vec3 vecReflected = reflect(incidente, normal);
        r_out.push_back(Ray(rec.p, vecReflected));
        color.push_back(specular);
    } else {
        r_out.push_back(Ray(rec.p, vecRefracted));

        vec3 dTransparency = colorTransparency(transparency, rec.d);
        color.push_back(dTransparency);
        //color.push_back(transparency);
    }
    return true;
}

vec3 colorTransparency(vec3 color, float d){
    if(d == 0 && color == vec3(0,0,0)){
        return vec3(0,0,0);
    }
    vec3 r;
    r.x = glm::pow(color.x, d);
    r.y = glm::pow(color.y, d);
    r.z = glm::pow(color.z, d);
    return r;
}


