//
// Created by eudald on 4/1/20.
//

#include "ColorConversion.h"
#include <glm/gtx/color_space.inl>

vec3 rgbToHsl(vec3 rgb){
    vec3 hsv = glm::hsvColor(rgb);
    float h = hsv.x, s = hsv.y, v = hsv.z;
    vec3 hsl;
    hsl.x = h;
    hsl.z = v*(1.0f - s/2.0f);
    hsl.y = 0;
    if(hsl.z > 0 && hsl.z < 1){
        hsl.y = (v - hsl.z) / glm::min(hsl.z, 1-hsl.z);
    }
    return hsl;
}

vec3 hslToRgb(vec3 hsl){
    float h = hsl.x, s = hsl.y, l = hsl.z;
    vec3 hsv;
    hsv.x = h;
    hsv.z = l + s*glm::min(l, 1-l);
    hsv.y = 0;
    if(hsv.z > 0){
        hsv.y = 2*(1-l/hsv.z);
    }

    return glm::rgbColor(hsv);
}