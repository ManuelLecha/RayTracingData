//
// Created by rballeba50.alumnes on 2/3/20.
//

#ifndef RAYDATA_TRIANGLE_H
#define RAYDATA_TRIANGLE_H


#include "Object.h"
#include "Simplex.h"
#include "PlaneFigure.h"


class Triangle : public PlaneFigure {
public:
    Triangle(vec3 v1, vec3 v2, vec3 v3, float v);

    ~Triangle();

    virtual bool intersection(const Ray &r, float t_min, float t_max, IntersectionInfo &info) const;

    virtual void aplicaTG(TG *t);

    const vec3 getBaricentricCoordinates(const vec3 &p) const;

    virtual Parallelepiped getBoundaries();

    //TODO definir normals
    void translate(vec3 translation);

    void scale(double r);

private:
    Simplex *simplex;

    bool isPointInside(const vec3 &pBaricentricCoordinates) const;

    bool pIsVertex(const vec3 &p) const;


};


#endif //RAYDATA_TRIANGLE_H