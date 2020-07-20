//
// Created by Manuel Lecha Sánchez on 09/03/2020.
//

#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"

using namespace glm;


class Light {
public:
    Light(vec3 focus, vec3 diffuseComponent, vec3 specularComponent, vec3 ambientComponent, float a0, float a1,
          float a2);

    virtual ~Light() {}

    virtual float computeAttenuation(vec3 collisionPoint);

    virtual vec3 computeLightDirection(vec3 collisionPoint);

    vec3 focus;
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;

    float a0;
    float a1;
    float a2;

    float attenuation;

};


#endif //LIGHT_H
