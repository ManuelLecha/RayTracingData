//
// Created by Manuel Lecha Sánchez on 02/03/2020.
//

#ifndef DISK_H
#define DISK_H

#include "Plane.h"
#include "Animation.h"
#include "Translate.h"
#include "PlaneFigure.h"

class Disk : public PlaneFigure {

public:
    Disk(vec3 normal, vec3 center, float radius);

    virtual ~Disk() {};

    bool intersection(const Ray &r, float t_min, float t_max, IntersectionInfo &info) const;

    void aplicaTG(TG *t);
    vec3 center;
private:
    vec3 normal;

    float radius;
};


#endif //DISK_H
