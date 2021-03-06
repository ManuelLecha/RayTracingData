/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef SPHEREH
#define SPHEREH

#include "Object.h"
#include "Animation.h"
#include "Translate.h"


class Sphere : public Object {
public:
    Sphere(vec3 cen, float r, float data);

    virtual ~Sphere() {}

    virtual bool intersection(const Ray &ray, float t_min, float t_max, IntersectionInfo &info) const;

    virtual void aplicaTG(TG *t);

    virtual Parallelepiped getBoundaries();

private:
    // Centre de l'esfera
    vec3 center;
    // Radi de l'esfera
    float radius;

};


#endif



