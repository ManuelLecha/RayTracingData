//
// Created by ruben on 28/3/20.
//

#ifndef RAYDATA_DATATEMPLATE_H
#define RAYDATA_DATATEMPLATE_H


#include <map>
#include "Material.h"
#include "Lambertian.h"

class DataTemplate {
public:
    virtual ~DataTemplate();

    DataTemplate();

    vec3 getColor(int colorMapId, float value);

    Material *getMaterial(int matId, vec3 color);

private:

};


#endif //RAYDATA_DATATEMPLATE_H
