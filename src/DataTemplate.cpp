//
// Created by ruben on 28/3/20.
//

#include <include/Metal.h>
#include "DataTemplate.h"
#include "ColorMap.h"
#include "ColorMapStatic.h"
#include "BaseMaterial.h"

DataTemplate::DataTemplate() {
}

DataTemplate::~DataTemplate() {
}

vec3 DataTemplate::getColor(int colorMapId, float value) {
    //COLOR
    vec3 color;
    switch (colorMapId) {
        case 0:
            return ColorMapStatic(ColorMapStatic::COLOR_MAP_TYPE_INFERNO).getColor(value);
        case 1:
            return ColorMapStatic(ColorMapStatic::COLOR_MAP_TYPE_JET).getColor(value);
        case 2:
            return ColorMapStatic(ColorMapStatic::COLOR_MAP_TYPE_MAGMA).getColor(value);
        case 3:
            return ColorMapStatic(ColorMapStatic::COLOR_MAP_TYPE_PARULA).getColor(value);
        case 4:
            return ColorMapStatic(ColorMapStatic::COLOR_MAP_TYPE_PLASMA).getColor(value);
        case 5:
            return ColorMapStatic(ColorMapStatic::COLOR_MAP_TYPE_VIRIDIS).getColor(value);
    }
    return ColorMapStatic(ColorMapStatic::COLOR_MAP_TYPE_INFERNO).getColor(value);
}

Material *DataTemplate::getMaterial(int matId, vec3 color) {
    switch (matId) {
        case 1:
            return new Metal(
                    vec3(0.1, 0.1, 0.1),
                    color,
                    vec3(0.7, 0.7, 0.7),
                    10,
                    vec3(0, 0, 0)
            );
        case 2: {
            Material *m = new BaseMaterial(color);
            return m;
        }
        case 3:
            return new Lambertian(color);

    }
    Material *m = new BaseMaterial(color);
    return m;
}
