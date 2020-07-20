//
// Created by eudald on 3/30/20.
//

#ifndef RAYDATA_LIGHTFACTORY_H
#define RAYDATA_LIGHTFACTORY_H

#include "Light.h"
#include "Scene.h"


class LightFactory {
public:
    LightFactory(Scene *s);

    void addLightArea(vec3 center, vec3 right, vec3 up, Light sample, int horizontalLights, int verticalLights);

    Scene *s;
};


#endif //RAYDATA_LIGHTFACTORY_H
