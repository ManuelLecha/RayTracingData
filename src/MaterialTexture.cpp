//
// Created by Manuel Lecha Sánchez on 25/03/2020.
//

#include "MaterialTexture.h"

#define NUMBER_OF_RAYS_SCATTER 3


MaterialTexture::MaterialTexture(Texture *texture, TextureMap* tmap) {
    this->texture = texture;
    map = tmap;
}

bool MaterialTexture::scatter(const Ray &r_in, const IntersectionInfo &rec, std::vector<vec3> &colors,
                              std::vector<Ray> &r_out) const {
    //When material has a texture we do not have scatter any ray, so we return false
    //Extension: make texture scatter with the texture color
    vec2 uv = map->getUVFromSurfacePoint(rec.p);
    vec3 diffuseColor = getDiffuse( uv);
    for(int i=0; i < NUMBER_OF_RAYS_SCATTER; i++) {
        vec3 target = rec.p + 4.0f*rec.normal + this->RandomInSphere();
        r_out.push_back(Ray(rec.p, target - rec.p));
        colors.push_back(diffuseColor);
    }
    return true;
}

//This method returns the color pixel of the corresponding point of the texture image
vec3 MaterialTexture::getDiffuse(vec2 point) const {
    return this->texture->getColorPixel(point);
}

MaterialTexture::~MaterialTexture() {}