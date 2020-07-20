//
// Created by Manuel Lecha Sánchez on 02/03/2020.
//

#ifndef CYLINDER_H
#define CYLINDER_H

#include "Object.h"
#include "Disk.h"

class Cylinder : public Object {

public:
    Cylinder(vec3 centre, float radius, float height, float v);

    ~Cylinder();

    virtual bool intersection(const Ray &r, float t_min, float t_max, IntersectionInfo &info) const;

    virtual void aplicaTG(TG *t);

    virtual Parallelepiped getBoundaries();

private:
    vec3 center;
    float radius;
    float height;
    Disk *topDisk;
    Disk *bottomDisk;
};


#endif //CYLINDER_H
