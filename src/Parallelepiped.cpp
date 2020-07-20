//
// Created by ruben on 3/3/20.
//

#include "Parallelepiped.h"

Parallelepiped::Parallelepiped(vec3 pmin, vec3 pmax) {
    this->pmin = pmin;
    this->pmax = pmax;
}

vec3 Parallelepiped::getPmin() {
    return this->pmin;
}

vec3 Parallelepiped::getPmax() {
    return this->pmax;
}
