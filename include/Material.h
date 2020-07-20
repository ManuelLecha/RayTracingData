#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include "Ray.h"
#include "Hitable.h"


class Object;

// Classe abstracte Material. Totes les seves filles hauran de definir el metode abstracte sccater
class Material {
public:

    Material();

    Material(vec3 a, vec3 d, vec3 s, float sh, vec3 transparency);

    ~Material();

    //Added this method to call it at bling phong and override it at Material Texture to return the pixel color of the texture
    virtual vec3 getDiffuse(vec2 point) const;

    virtual bool
    scatter(const Ray &r_in, const IntersectionInfo &rec, std::vector<vec3> &color, std::vector<Ray> &r_out) const = 0;

    //Material components
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    vec3 transparency;
    vec3 transparencyComplementary;
    float shininess;

protected:
    vec3 RandomInSphere() const;
};

#endif // MATERIAL_H
