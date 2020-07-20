#include <include/Triangle.h>
#include <include/Cylinder.h>
#include "ObjectFactory.h"
#include <string>
#include <include/BoundaryObject.h>
#include <include/Metal.h>
#include <include/Transparent.h>
#include <include/Scale.h>

ObjectFactory *ObjectFactory::instance = nullptr;

ObjectFactory::ObjectFactory() {
}


map<std::string, ObjectFactory::OBJECT_MATERIALS> ObjectFactory::mapMaterials = {
        {"METAL",       ObjectFactory::METAL},
        {"LAMBERTIAN",  ObjectFactory::LAMBERTIAN},
        {"TRANSPARENT", ObjectFactory::TRANSPARENT}
};


Object *
ObjectFactory::createObject(OBJECT_TYPES t, OBJECT_MATERIALS m, double values[], QString fileLoad, double dataValue) {
    Object *o; //Object to create
    switch (t) {
        case SPHERE:
            o = new Sphere(
                    vec3(values[0], values[1], values[2]),
                    values[3],
                    dataValue
            );

            o->setMaterial(createMaterial(
                    m,
                    vec3(values[4], values[5], values[6]),
                    vec3(values[7], values[8], values[9]),
                    vec3(values[10], values[11], values[12]),
                    values[13],
                    values[14],
                    vec3(values[15], values[16], values[17])
            ));
            break;
        case TRIANGLE:
            o = new Triangle(
                    vec3(values[0], values[1], values[2]),
                    vec3(values[3], values[4], values[5]),
                    vec3(values[6], values[7], values[8]),
                    dataValue
            );

            o->setMaterial(createMaterial(
                    m,
                    vec3(values[9], values[10], values[11]),
                    vec3(values[12], values[13], values[14]),
                    vec3(values[15], values[16], values[17]),
                    values[18],
                    values[19],
                    vec3(values[20], values[21], values[22])
            ));
            break;
        case CYLINDER:
            o = new Cylinder(
                    vec3(values[0], values[1], values[2]),
                    values[3],
                    values[4],
                    dataValue
            );

            o->setMaterial(createMaterial(
                    m,
                    vec3(values[5], values[6], values[7]),
                    vec3(values[8], values[9], values[10]),
                    vec3(values[11], values[12], values[13]),
                    values[14],
                    values[15],
                    vec3(values[16], values[17], values[18])
            ));
            break;

        case PLANE:
            o = new Plane(
                    vec3(values[0], values[1], values[2]),
                    vec3(values[3], values[4], values[5]),
                    dataValue
            );

            o->setMaterial(createMaterial(
                    m,
                    vec3(values[6], values[7], values[8]),
                    vec3(values[9], values[10], values[11]),
                    vec3(values[12], values[13], values[14]),
                    values[15],
                    values[16],
                    vec3(values[17], values[18], values[19])
            ));
            break;

        case BROBJECT:
            vec3 center = vec3(values[0], values[1], values[2]); //todo
            double scale = values[3]; //todo
            o = new BoundaryObject(fileLoad, dataValue); //todo preguntar Y el center, la escala, el data?
            Scale s(vec3(scale, scale, scale));
            Translate t(center);
            o->aplicaTG(&s);
            o->aplicaTG(&t);

            o->setMaterial(createMaterial(
                    m,
                    vec3(values[4], values[5], values[6]),
                    vec3(values[7], values[8], values[9]),
                    vec3(values[10], values[11], values[12]),
                    values[13],
                    values[14],
                    vec3(values[15], values[16], values[17])
            ));
            break;
    }
    return o;
}

Material *ObjectFactory::createMaterial(ObjectFactory::OBJECT_MATERIALS m, const vec3 &ambient, const vec3 &diffuse,
                                        const vec3 &specular,
                                        double shininess, double idxRef, vec3 transparency) {
    switch (m) {
        case LAMBERTIAN:
            return new Lambertian(ambient, diffuse, specular, shininess, transparency);
            break;
        case METAL:
            return new Metal(ambient, diffuse, specular, shininess, transparency);
            break;
        case TRANSPARENT:
            return new Transparent(ambient, diffuse, specular, shininess, idxRef, transparency);
    }
}

Material *ObjectFactory::createMaterial(ObjectFactory::OBJECT_MATERIALS m, const vec3 &color) {
    switch (m) {
        case LAMBERTIAN:
            return new Lambertian(color);
            break;
        case METAL:
            return new Metal(color);
            break;
        case TRANSPARENT:
            return new Transparent(color);
            break;
    }
}

ObjectFactory::OBJECT_MATERIALS ObjectFactory::getMaterialFromText(std::string name) {
    return mapMaterials.at(name);
}
