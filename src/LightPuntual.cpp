//
// Created by Manuel Lecha Sánchez on 09/03/2020.
//

#include "LightPuntual.h"

LightPuntual::LightPuntual(vec3 focus, vec3 ambient, vec3 diffuse, vec3 specular, float a0, float a1, float a2) :
        Light(focus, diffuse, specular, ambient, a0, a1, a2) {}
