//
// Created by eudald on 3/30/20.
//

#include "LightFactory.h"

LightFactory::LightFactory(Scene *s) {
    this->s = s;
}

void
LightFactory::addLightArea(vec3 center, vec3 right, vec3 up, Light sample, int horizontalLights, int verticalLights) {
    if (horizontalLights <= 1 || verticalLights <= 1) {
        return;
    }

    float numLights = horizontalLights + verticalLights;

    for (int i = 0; i < horizontalLights; i++) {
        for (int j = 0; j < horizontalLights; j++) {
            vec3 lp = center + right * (float(i) / (horizontalLights - 1)) + up * (float(j) / (verticalLights - 1));
            s->lights.push_back(
                    new Light(lp, sample.diffuse / numLights, sample.specular / numLights, sample.ambient / numLights,
                              sample.a0, sample.a1, sample.a2));
        }
    }
}