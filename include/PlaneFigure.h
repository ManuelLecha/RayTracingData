//
// Created by ruben on 3/3/20.
//

#ifndef PLANEFIGURE_H
#define PLANEFIGURE_H


#include "Object.h"
#include "Plane.h"

class PlaneFigure : public Object {
public:
    PlaneFigure(vec3 normal, vec3 pass_point, float v);

    virtual ~PlaneFigure();

    PlaneFigure(vec3 normal, vec3 pass_point);

    Plane *getPlaneContaining() const;

    virtual Parallelepiped getBoundaries() { return Parallelepiped(vec3(0, 0, 0), vec3(0, 0, 0)); };
private:
    Plane *planeContaining;
};


#endif //PLANEFIGURE_H
