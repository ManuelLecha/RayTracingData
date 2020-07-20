//
// Created by anna on 18/01/2020.
//

#include <include/LightPuntual.h>
#include <include/Metal.h>
#include <include/Transparent.h>
#include <include/Cylinder.h>
#include "SceneFactoryVirtual.h"


SceneFactoryVirtual::SceneFactoryVirtual() {
}

Scene *SceneFactoryVirtual::createScene(QString filename) {
    Scene *s = new Scene();
    SceneReader *sc = new SceneReader(s);
    sc->readFile(filename);
    s->createSceneBoundaries();
    s->setAmbientGlobalLight(vec3(0.5, 0.5, 0.5));
    return s;
}

Scene *SceneFactoryVirtual::createScene() {
    Scene *s = new Scene();
    this->TestFase2(s);
    return s;
}

void SceneFactoryVirtual::TestFase2(Scene *s) {

    Sphere *sphereSmall = new Sphere(vec3(1, 0, -1), 0.5, 1.0);
    sphereSmall->setMaterial(
            new Lambertian(vec3(0.2, 0.2, 0.2), vec3(0.5, 0.5, 0.5), vec3(1.0, 1.0, 1.0), 10.0, vec3(0, 0, 0)));

    Sphere *sphereMedium = new Sphere(vec3(-3.0, 1, 1), 1, 1.0);
    sphereMedium->setMaterial(
            new Metal(vec3(0.2, 0.2, 0.2), vec3(0.7, 0.6, 0.5), vec3(0.7, 0.7, 0.7), 10.0, vec3(0, 0, 0)));

    Sphere *sphereMedium2 = new Sphere(vec3(0.0, 0.5, 0.0), 0.5, 1.0);
    sphereMedium2->setMaterial(new Transparent(vec3(0.0, 0.0, 1.0), vec3(0.0, 0.0, 1.0), vec3(0.0, 0.0, 1.0), 1.0, 1.5,
                                               vec3(0.8, 0.8, 0.8)));

    Sphere *sphereMedium3 = new Sphere(vec3(1.2, 1.7, 1.2), 0.5, 1.0);
    sphereMedium3->setMaterial(new Transparent(vec3(1.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0), 1.0, 1.0,
                                               vec3(0.75, 0.75, 0.75)));

    Sphere *sphereBig = new Sphere(vec3(0.0, -100.5, -1.0), 100.0, 1.0);
    sphereBig->setMaterial(new Lambertian(vec3(0.2, 0.2, 0.2), vec3(0.8, 0.8, 0.0), vec3(0.3, 1.0, 1.0), 10.0, vec3(0.0, 0.0, 0.0)));

    Cylinder *cylinder = new Cylinder(vec3(3.0, 0.0, -1.0), 0.5, 1.1, 1.0);
    cylinder->setMaterial( new Transparent(vec3(1.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0), 1.0, 1.0,
                                       vec3(0.75, 0.75, 0.75)));

//    Animation *anim = new Animation();
//    anim->transf = new Translate(vec3(0.2));
//    sphere->addAnimation(anim);

    s->objects.push_back(sphereSmall);
    s->objects.push_back(sphereMedium);
    s->objects.push_back(cylinder);
    s->objects.push_back(sphereMedium2);
    //s->objects.push_back(sphereMedium3);
    s->objects.push_back(sphereBig);
    //Setting global light fase 2
    s->setAmbientGlobalLight(vec3(0.1, 0.1, 0.1));
    //Adding a punctual light
    LightPuntual *uniqueLight = new LightPuntual(
            vec3(10, 10, 2.0),
            vec3(0.3, 0.3, 0.3),
            vec3(0.7, 0.7, 0.7),
            vec3(1.0, 1.0, 1.0),
            0.5, 0.0, 0.01);
    s->lights.push_back(uniqueLight);
    //Setting dimensions Fase 2
    s->setDimensions(vec3(-5, -5, -5), vec3(5, 5, 5));
}

Camera *SceneFactoryVirtual::createCamera() {
    // creacio de la camera
    vec3 lookfrom(13.0, 2.0, 3.0);
    vec3 lookat(0.0, 0.0, 0.0);
    float dist_to_focus = length(lookfrom - lookat);
    float aperture = 0.1;
    int pixelsX = 600;
    int pixelsY = 300;
    return (new Camera(lookfrom, lookat, vec3(0, 1, 0), 20, pixelsX, pixelsY, aperture, dist_to_focus));
}
