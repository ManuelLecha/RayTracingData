//
// Created by Manuel Lecha Sánchez on 02/03/2020.
//

#include "Disk.h"
#include <math.h>

Disk::Disk(vec3 normal, vec3 center, float radius) : PlaneFigure(normal, center, radius) {
    this->normal = normal;
    this->center = center;
    this->radius = radius;
}

bool Disk::intersection(const Ray &r, float t_min, float t_max, IntersectionInfo &info) const {

    if (getPlaneContaining()->intersection(r, t_min, t_max, info)) {
        if (length(info.p - this->center) < this->radius) {
            return true;
        }
    }

    return false;
}

void Disk::aplicaTG(TG *t) {
    //TODO
}
