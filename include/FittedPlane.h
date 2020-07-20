//
// Created by acatalta11.alumnes on 2/3/20.
//

#ifndef GIVD_BOUNDEDPLANE_H
#define GIVD_BOUNDEDPLANE_H

#include "Object.h"
#include "Plane.h"
#include "Animation.h"
#include "Translate.h"
#include "glm/gtx/constants.hpp"
#include "TextureMap.h"


class FittedPlane : public Plane, public TextureMap {
public:
    FittedPlane(vec3 center, vec3 up, vec3 right);

    virtual bool intersection(const Ray &r, float t_min, float t_max, IntersectionInfo &info) const;
    virtual vec2 getUVFromSurfacePoint(vec3 point);

    Parallelepiped getBoundaries();

    vec2 projectPlane(vec3 surfacePoint);


public:
    vec3 center;
    vec3 up;
    vec3 right;
    float upLength;
    float rightLength;
};


#endif //GIVD_BOUNDEDPLANE_H
