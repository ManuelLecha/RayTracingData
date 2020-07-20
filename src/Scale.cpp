//
// Created by eudald on 4/2/20.
//

#include "Scale.h"

Scale::Scale(glm::vec3 scale){
    this->scale = scale;
    matTG = glm::scale(glm::mat4(1.0f), scale);
}
