#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Ray.h"
#include "Hitable.h"
#include "Animation.h"
#include "Object.h"
#include "Sphere.h"
#include "BoundaryObject.h"
#include "Lambertian.h"
#include "ColorMap.h"
#include "FittedPlane.h"
#include "Light.h"
#include "Camera.h"

class Scene : public Hitable {
public:
    Scene();

    virtual ~Scene();

    // Funcio que calcula la interseccio del raig r amb l'escena. Guarda la informacio
    // del punt d'interseccio més proper a t_min, punt que està entre t_min i t_max.
    // Retorna cert si existeix la interseccio, fals, en cas contrari
    virtual bool intersection(const Ray &raig, float t_min, float t_max, IntersectionInfo &info) const;

    virtual std::vector<IntersectionInfo> multipleIntersection(const Ray &raig, float t_min, float t_max) const;

    // Funcio recursiva que calcula el color. Inicialment es
    // es crida a cada pixel. Tambe es crida en calcular les ombres o les reflexions.
    vec3 ComputeColorRay(Ray &ray);

    vec3 getShadowFactor(vec3 intersectionPoint, Light *l, vec3 PL);

    void update(int nframe);

    void setMaterials(ColorMap *cm);

    void setDimensions(vec3 p1, vec3 p2);

    void setAmbientGlobalLight(vec3 value);

    void createSceneBoundaries();

    // Dimensions de l'escena virtual
    vec3 pmin, pmax;
    // Vector d'objectes continguts a l'escena
    std::vector<Object *> objects;
    //Lights contained in the Scene
    std::vector<Light *> lights;
    //Ambient global light
    vec3 ambientGlobalLight;
    static const int MIN_T_INTERSECTION = 0;
    constexpr static const float AMBIENT_REFRACTION_IDX = 1.0;
    FittedPlane *basePlane = nullptr;


private:
    vec3 getObjectIntersectionColor(Ray &ray, IntersectionInfo &intersectionInfo, int depth);

    vec3 Blinn_Phong(Ray &ray, IntersectionInfo &info);

    vec3 getBackgroundColor(Ray &ray);

};

#endif // SCENE_H
