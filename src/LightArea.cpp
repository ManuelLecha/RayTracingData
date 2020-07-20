//
// Created by eudald on 3/30/20.
//

#include "LightArea.h"

LightArea::LightArea(vec3 center, vec3 up, vec3 right, vec3 ambientComponent, vec3 diffuseComponent,
                     vec3 specularComponent) :
        Light(center, diffuseComponent, specularComponent, ambientComponent, 0, 0, 0), FittedPlane(center, up, right) {

}


float attFunction(float d, float a0, float a1, float a2) {
    return 1.0 / ((float) (a2 * pow(d, 2) + a1 * d + a0));
}

float LightArea::computeAttenuation(vec3 collisionPoint) {
    return Light::computeAttenuation(collisionPoint);
    /*vec2 proj = projectPlane(collisionPoint);
    vec3 closestPoint = proj.x * right + proj.y * up;
    return attFunction(glm::length(collisionPoint - closestPoint), a0, a1, a2);*/
}


vec3 LightArea::computeLightDirection(vec3 collisionPoint) {
    if (glm::length(collisionPoint - center) > 2e64) {
        return glm::normalize(center - collisionPoint);
    }

    vec3 r = right * rightLength * 2.0f;
    vec3 u = up * upLength * 2.0f;
    vec3 o = center - right - up;

    vec3 sum(0, 0, 0);
    for (int i = 0; i <= 4; i++) {
        for (int j = 0; j <= 4; j++) {
            vec3 lp = o + r * (i / 4.0f) + u * (j / 4.0f);
            vec3 ldir = lp - collisionPoint;
            sum += glm::normalize(ldir) / glm::length(ldir);
        }
    }
    vec3 result = glm::normalize(sum);
    return result;
}
