
#include "Light.h"
#include <math.h>

Light::Light(vec3 focus, vec3 diffuseComponent, vec3 specularComponent, vec3 ambientComponent, float a0, float a1,
             float a2) {
    this->focus = focus;
    this->diffuse = diffuseComponent;
    this->specular = specularComponent;
    this->ambient = ambientComponent;
    this->a0 = a0;
    this->a1 = a1;
    this->a2 = a2;
}

float Light::computeAttenuation(vec3 collisionPoint) {
    float d = distance(this->focus, collisionPoint);
    return 1.0 / ((float) (this->a2 * pow(d, 2) + this->a1 * d + this->a0));
}

vec3 Light::computeLightDirection(vec3 collisionPoint) {
    return glm::normalize(this->focus - collisionPoint);
}
