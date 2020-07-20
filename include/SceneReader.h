#ifndef SCENEREADER_H
#define SCENEREADER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <vector>
#include "glm/glm.hpp"
#include "Scene.h"

/*
 *  Posicion 00: Tipo [sphere, base, brobject...]
 *
 *  Formato para sphere:
 *  Posicion 01:    Sphere Centro X
 *  Posicion 02:    Sphere Centro Y
 *  Posicion 03:    Sphere Centro Z
 *  Posicion 04:    Sphere Radio
 *  Posicion 05:    Material ambient X
 *  Posicion 06:    Material ambient Y
 *  Posicion 07:    Material ambient Z
 *  Posicion 08:    Material difusa X
 *  Posicion 09:    Material difusa Y
 *  Posicion 10:    Material difusa Z
 *  Posicion 11:    Material especular X
 *  Posicion 12:    Material especular Y
 *  Posicion 13:    Material especular Z
 *  Posicion 14:    Shininess
 *  Posicion 15:    Tipo de material
 *  Posicion 16:    Idx Refraccio
 *  Posicion 17:    Transparency 1
 *  Posicion 18:    Transparency 2
 *  Posicion 19:    Transparency 3
 *
 *  Formato para Triangle:
 *  Posicion 01:    Triangle vertex 1 X
 *  Posicion 02:    Triangle vertex 1 Y
 *  Posicion 03:    Triangle vertex 1 Z
 *  Posicion 04:    Triangle vertex 2 X
 *  Posicion 05:    Triangle vertex 2 Y
 *  Posicion 06:    Triangle vertex 2 Z
 *  Posicion 07:    Triangle vertex 3 X
 *  Posicion 08:    Triangle vertex 3 Y
 *  Posicion 09:    Triangle vertex 3 Z
 *  Posicion 10:    Material ambient X
 *  Posicion 11:    Material ambient Y
 *  Posicion 12:    Material ambient Z
 *  Posicion 13:    Material difusa X
 *  Posicion 14:    Material difusa Y
 *  Posicion 15:    Material difusa Z
 *  Posicion 16:    Material especular X
 *  Posicion 17:    Material especular Y
 *  Posicion 18:    Material especular Z
 *  Posicion 19:    Shininess
 *  Posicion 20:    Tipo de material
 *  Posicion 21:    Idx Refraccio
 *  Posicion 22:    Transparency 1
 *  Posicion 23:    Transparency 2
 *  Posicion 24:    Transparency 3

 *  Formato para Cylinder:
 *  Posicion 01:    Cylinder Centro X
 *  Posicion 02:    Cylinder Centro Y
 *  Posicion 03:    Cylinder Centro Z
 *  Posicion 04:    Cylinder Radio
 *  Posicion 05:    Cylinder Altura
 *  Posicion 06:    Material ambient X
 *  Posicion 07:    Material ambient Y
 *  Posicion 08:    Material ambient Z
 *  Posicion 09:    Material difusa X
 *  Posicion 10:    Material difusa Y
 *  Posicion 11:    Material difusa Z
 *  Posicion 12:    Material especular X
 *  Posicion 13:    Material especular Y
 *  Posicion 14:    Material especular Z
 *  Posicion 15:    Shininess
 *  Posicion 16:    Tipo de material
 *  Posicion 17:    Idx Refraccio
 *  Posicion 18:    Transparency 1
 *  Posicion 19:    Transparency 2
 *  Posicion 20:    Transparency 3
 *
 *   *  Formato para BoundaryObject:
 *  Posicion 01:    BoundaryObject filename de objeto
 *  Posicion 02:    BoundaryObject Centro X
 *  Posicion 03:    BoundaryObject Centro Y
 *  Posicion 04:    BoundaryObject Centro Z
 *  Posicion 05:    BoundaryObject escala
 *  Posicion 06:    Material ambient X
 *  Posicion 07:    Material ambient Y
 *  Posicion 08:    Material ambient Z
 *  Posicion 09:    Material difusa X
 *  Posicion 10:    Material difusa Y
 *  Posicion 11:    Material difusa Z
 *  Posicion 12:    Material especular X
 *  Posicion 13:    Material especular Y
 *  Posicion 14:    Material especular Z
 *  Posicion 15:    Shininess
 *  Posicion 16:    Tipo de material
 *  Posicion 17:    Idx Refraccio
 *  Posicion 18:    Transparency 1
 *  Posicion 19:    Transparency 2
 *  Posicion 20:    Transparency 3
 *
 *  Formate para base
 *  Posicion 01:    tipo de base: plane o sphere
 *  Posicion 02:    En caso de plane Normal X, sphere Centro X
 *  Posicion 03:    En caso de plane Normal Y, sphere Centro Y
 *  Posicion 04:    En caso de plane Normal Z, sphere Centro Z
 *  Posicion 05:    En caso de plane D, sphere r
 *  Posicion 06:    Material ambient X
 *  Posicion 07:    Material ambient Y
 *  Posicion 08:    Material ambient Z
 *  Posicion 09:    Material difusa X
 *  Posicion 10:    Material difusa Y
 *  Posicion 11:    Material difusa Z
 *  Posicion 12:    Material especular X
 *  Posicion 13:    Material especular Y
 *  Posicion 14:    Material especular Z
 *  Posicion 15:    Shininess
 *  Posicion 16:    Tipo de material
 *  Posicion 17:    Texture resource (e,g, ://resources/map.png)
 *  Posicion 18;    Idx Refraccio
 *  Posicion 19:    Transparency 1
 *  Posicion 20:    Transparency 2
 *  Posicion 21:    Transparency 3
 *
 *  Formato para luz puntual
 *  Posicion 01:    Foco X
 *  Posicion 02:    Foco Y
 *  Posicion 03:    Foco  Z
 *  Posicion 04:    Material ambient X
 *  Posicion 05:    Material ambient Y
 *  Posicion 06:    Material ambient Z
 *  Posicion 07:    Material difusa X
 *  Posicion 08:    Material difusa Y
 *  Posicion 09:    Material difusa Z
 *  Posicion 10:    Material especular X
 *  Posicion 11:    Material especular Y
 *  Posicion 12:    Material especular Z
 *  Posicion 13:    a0
 *  Posicion 14:    a1
 *  Posicion 15:    a2
 */

class SceneReader {
public:
    explicit SceneReader();

    SceneReader(Scene *s);

    void readFile(QString fileName);

protected:
    virtual void fileLineRead(QString lineReaded);

    Scene *scene;

    void sphereFound(QStringList list);

    void triangleFound(QStringList fields);

    void cylinderFound(QStringList fields);

    void baseFound(QStringList list);

    void BrObjectFound(QStringList fields);

    void lightFound(QStringList fields);
};

#endif // SCENEREADER_H
