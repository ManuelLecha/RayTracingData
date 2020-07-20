//
// Created by ruben on 3/3/20.
//

#ifndef RAYDATA_PARALLELEPIPED_H
#define RAYDATA_PARALLELEPIPED_H

#include <glm/glm.hpp>

using namespace glm;

class Parallelepiped {
public:
    Parallelepiped(vec3 pmin, vec3 pmax);

    virtual ~Parallelepiped() {};

    vec3 getPmin();

    vec3 getPmax();

private:
    vec3 pmin;
    vec3 pmax;
};


#endif //RAYDATA_PARALLELEPIPED_H
