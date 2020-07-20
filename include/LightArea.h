//
// Created by eudald on 3/30/20.
//

#ifndef RAYDATA_LIGHTAREA_H
#define RAYDATA_LIGHTAREA_H

#include "Light.h"
#include "FittedPlane.h"


class LightArea : public Light, protected FittedPlane {
public:
    LightArea(vec3 center, vec3 up, vec3 right, vec3 ambientComponent, vec3 diffuseComponent, vec3 specularComponent);

    virtual float computeAttenuation(vec3 collisionPoint);

    virtual vec3 computeLightDirection(vec3 collisionPoint);
};


#endif //RAYDATA_LIGHTAREA_H
