//
// Created by eudald on 4/2/20.
//

#ifndef RAYDATA_TEXTUREMAP_H
#define RAYDATA_TEXTUREMAP_H

#include <glm/core/type.hpp>

class TextureMap {
public:
    virtual glm::vec2 getUVFromSurfacePoint(glm::vec3 point)=0;
};


#endif //RAYDATA_TEXTUREMAP_H
