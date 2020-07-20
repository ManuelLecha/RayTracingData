//
// Created by Manuel Lecha Sánchez on 25/03/2020.
//

#ifndef MATERIALTEXTURE_H
#define MATERIALTEXTURE_H

#include "Texture.h"
#include "Material.h"
#include "TextureMap.h"

class MaterialTexture : public Material {
public:
    MaterialTexture(Texture *texture, TextureMap* tmap);

    virtual bool scatter(const Ray &r_in, const IntersectionInfo &rec, std::vector<vec3> &colors,
                         std::vector<Ray> &r_out) const override;

    ~MaterialTexture();

    vec3 getDiffuse(vec2 point) const override;

private:
    Texture *texture;
    TextureMap* map;
};


#endif //MATERIALTEXTURE_H
