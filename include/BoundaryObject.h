#ifndef BOUNDARYOBJECT_H
#define BOUNDARYOBJECT_H

#include <vector>
#include <string>

#include <iostream>
#include <stdlib.h>
#include <cstring>

#include <QString>
#include <QFile>
#include <QRegularExpression>

#include "Object.h"
#include "Cara.h"
#include "ReadFile.h"
#include "Triangle.h"

using namespace std;

class BoundaryObject : public Object {
public:
    BoundaryObject(string s, float data);

    BoundaryObject(const QString &fileName, float data);

    virtual bool intersection(const Ray &r, float t_min, float t_max, IntersectionInfo &info) const;

    virtual ~BoundaryObject();

    virtual void aplicaTG(TG *t);

    vec3 getObjectCenter();

public:

    string nom;
    vector<Cara> cares; // cares de l'objecte
    vector<vec4> vertexs; // vertexs de l'objecte sense repetits
    void readObj(string filename);

    void construeix_cara(char **words, int nwords, BoundaryObject *objActual, int vindexUlt);

};

#endif // BOUNDARYOBJECT_H
