//
// Created by Manuel Lecha Sánchez on 09/03/2020.
//

#ifndef LIGHTPUNTUAL_H
#define LIGHTPUNTUAL_H


#include "Light.h"

class LightPuntual : public Light {
public:
    LightPuntual(vec3 focus, vec3 a, vec3 d, vec3 s, float a0, float a1, float a2);

    ~LightPuntual() {}


};


#endif //RAYDATA_LIGHTPUNTUAL_H
