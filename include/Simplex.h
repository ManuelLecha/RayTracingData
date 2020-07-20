//
// Created by rballeba50.alumnes on 2/3/20.
//

#ifndef RAYDATA_SIMPLEX_H
#define RAYDATA_SIMPLEX_H

#include "Object.h"

class Simplex {
public:
    Simplex(vec3 v1, vec3 v2, vec3 v3);

    virtual ~Simplex() {}

    vec3 getV1();

    vec3 getV2();

    vec3 getV3();

    double calculateTriangleArea() const;

private:
    vec3 v1;
    vec3 v2;
    vec3 v3;
};


#endif //RAYDATA_SIMPLEX_H
