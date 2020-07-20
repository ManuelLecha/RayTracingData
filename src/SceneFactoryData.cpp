#include <include/LightPuntual.h>
#include "SceneFactoryData.h"
#include "LightArea.h"
#include "LightFactory.h"

SceneFactoryData::SceneFactoryData() {

}

Camera *SceneFactoryData::createCamera() {

    //vec3 lookfrom(0,2,-1);
    //FASE 3 - 1
    vec3 lookfrom(0, 30, -30);
    //vec3 dir = -lookfrom;
    //vec3 lookat = lookfrom + dir*4.0f;
    //FASE 3 - 1
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 4;

    //float aperture = 0.2;
    //float aperture = 0.5; //Fase 0 : Canviant l'opertura
    //FASE 3 - 1
    float aperture = 30;
    int pixelsX = 600;
    int pixelsY = 400;

    return (new Camera(lookfrom, lookat, vec3(0, 1, 0), 90, pixelsX, pixelsY, aperture, dist_to_focus));

}

Scene *SceneFactoryData::createScene(QString filename) {

    Scene *s = new Scene();
    s->setDimensions(vec3(-50, -1, -50), vec3(50, 1, 50));
    //FASE 3: Apartat 1
    //s->setDimensions(vec3(-5, -1, -5), vec3(5, 1, 5));
    DataReader *sc = new DataReader(s);
    // TODO: Fase 1: construccio de l'escena dins de dataReader
    sc->readFile(filename);
    //s->createSceneBoundaries();// preguntar eudald - albert si esto colisiona con su trabajo. Eudald: Era redudante, preguntame y te explico
    //Ambient light
    s->setAmbientGlobalLight(vec3(0.02, 0.02, 0.02));
    //fase 3 iluminacio puntual
    //Adding a punctual light



    LightArea *light4 = new LightArea(
            vec3(2, 30, 20),
            vec3(0, 5, -5),
            vec3(5, 0, 0),
            vec3(0.1, 0.1, 0.1),
            vec3(0.7, 0.7, 0.7),
            vec3(0.7, 0.7, 0.7));
    light4->a0 = 0.5;
    light4->a2 = 0.01;

    LightPuntual *light1 = new LightPuntual(
            vec3(2, 30, 10),
            vec3(0.1, 0.1, 0.1),
            vec3(0.7, 0.7, 0.7),
            vec3(0.7, 0.7, 0.7),
            0.5, 0, 0.01);
    LightPuntual *light2 = new LightPuntual(
            vec3(2, 30, 10),
            vec3(0.1, 0.1, 0.1),
            vec3(2, 2, 2),
            vec3(2, 2, 2),
            0.5, 0, 0.01);
    LightPuntual *light3 = new LightPuntual(
            vec3(2, 30, -10),
            vec3(0.1, 0.1, 0.1),
            vec3(0.7, 0.7, 0.7),
            vec3(0.7, 0.7, 0.7),
            0.5, 0, 0.01);

    LightFactory lightF(s);
    /*lightF.addLightArea(vec3(2, 10, 10),
                        vec3(0, 2, -2),
                        vec3(5, 0, 0),
                        *light2, 3, 3);*/


    s->lights.push_back(light1);
    s->lights.push_back(light2);
    s->lights.push_back(light3);
    //s->lights.push_back(light3);
    //s->lights.push_back(light4);
    //Setting dimensions Fase 2
    //Fi Fase 3 iluminacio puntual
    return s;
}

ColorMap *SceneFactoryData::createColorMap(ColorMapStatic::ColorMapType t) {
    ColorMap *cm = new ColorMapStatic(t);
    return cm;
}
