//
// Created by ruben on 3/3/20.
//

#include <iostream>
#include "PlaneFigure.h"


Plane *PlaneFigure::getPlaneContaining() const {
    return this->planeContaining;
}

PlaneFigure::PlaneFigure(vec3 normal, vec3 pass_point, float v) : Object(v) {
    planeContaining = new Plane(normal, pass_point, v);
}

PlaneFigure::PlaneFigure(vec3 normal, vec3 pass_point) {
    planeContaining = new Plane(normal, pass_point, -1);
}

PlaneFigure::~PlaneFigure() {
    delete (this->planeContaining);
}

