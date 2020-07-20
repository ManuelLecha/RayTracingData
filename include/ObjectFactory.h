#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include <string>
#include <QtCore/QString>
#include <map>

class ObjectFactory {
    static ObjectFactory *instance;

    ObjectFactory();

public:
    typedef enum {
        SPHERE,
        TRIANGLE,
        CYLINDER,
        PLANE,
        BROBJECT
    } OBJECT_TYPES;

    typedef enum {
        LAMBERTIAN,
        METAL,
        TRANSPARENT
    } OBJECT_MATERIALS;

    static OBJECT_MATERIALS getMaterialFromText(const std::string name);

    static ObjectFactory *getInstance() {
        if (instance == nullptr)
            instance = new ObjectFactory();
        return instance;
    }

    Object *getObject(double x, double y, double z, double val, OBJECT_TYPES t);

    ~ObjectFactory() {
        delete instance;
    }

    Object *createObject(OBJECT_TYPES t, OBJECT_MATERIALS m, double values[], QString fileLoad = nullptr,
                         double dataValue = -1);

private:
    static std::map<std::string, OBJECT_MATERIALS> mapMaterials;

    Material *
    createMaterial(OBJECT_MATERIALS m, const vec3 &ambient, const vec3 &diffuse, const vec3 &specular, double shininess,
                   double idxRef, vec3 transparency);

    Material *createMaterial(OBJECT_MATERIALS m, const vec3 &color);
};

#endif // OBJECTFACTORY_H
