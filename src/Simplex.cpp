//
// Created by rballeba50.alumnes on 2/3/20.
//

#include "Simplex.h"

Simplex::Simplex(vec3 v1, vec3 v2, vec3 v3) {
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
}

vec3 Simplex::getV1() {
    return this->v1;
}

vec3 Simplex::getV2() {
    return this->v2;
}

vec3 Simplex::getV3() {
    return this->v3;
}

double Simplex::calculateTriangleArea() const {
    vec3 baseNormalized = normalize(v2 - v1);
    vec3 heightNormalized = normalize(v3 - v1);
    double angle = acos(dot(baseNormalized, heightNormalized));
    double base = distance(v1, v2);
    double height = distance(v1, v3) * sin(angle);
    return (base * height) / 2.0;
}