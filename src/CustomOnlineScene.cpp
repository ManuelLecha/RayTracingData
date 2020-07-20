//
// Created by eudald on 4/1/20.
//
#include <iostream>
#include <include/AnimationDataReader.h>
#include "CustomOnlineScene.h"
#include "Camera.h"
#include "Scene.h"
#include "FittedPlane.h"
#include "Material.h"
#include "Sphere.h"
#include "DataTemplate.h"
#include "BaseMaterial.h"
#include "Transparent.h"
#include "Lambertian.h"
#include "LightPuntual.h"
#include "Render.h"
#include "RenderFactory.h"
#include "Metal.h"

void CustomOnlineScene::startScene1(int argc, char** argv, int c){
    vec3 lookfrom1(0, 30, 0.1);
    vec3 lookfrom2(3, 40, 30);
    vec3 lookfrom3(10, 27, 15);
    float vfov1 = 30;
    float vfov2 = 45;
    float vfov3 = 45;
    float vfov = vfov1;


    vec3 lookfrom = lookfrom1;

    if(c == 0){
        lookfrom = lookfrom1;
    }else if(c == 1){
        lookfrom = lookfrom2;
    }else if(c == 2){
        lookfrom = lookfrom3;
    }

    vec3 lookat(-0.25, 0, -0.25);
    float dist_to_focus = 4;
    float aperture = 30;
    int pixelsX = 1280;
    int pixelsY = 720;

    Camera* camera = new Camera(lookfrom, lookat, vec3(0, 1, 0), vfov, pixelsX, pixelsY, aperture, dist_to_focus);

    Scene* scene = new Scene();
    DataTemplate dt;
    //Base
    FittedPlane* base = new FittedPlane(vec3(0,0,0), vec3(0,0,50), vec3(-50,0,0));
    base->setMaterial(new Metal(vec3(0.25,0.25,0.25),vec3(0.90,0.78,0.45),vec3(0.9,0.78,0.45),50,vec3(0.2,0.2,0.2),0.1));
    FittedPlane* base2 = new FittedPlane(vec3(0,0,0), vec3(0,50,50), vec3(-50,0,0));
    base2->setMaterial(new Metal(vec3(0.25,0.25,0.25),vec3(0.2,0.2,0.2),vec3(0.0,0.0,0.0),50,vec3(0.6,0.6,0.6),0.1));
    //Material* grey_diffuse1 = new Lambertian(vec3(0.1, 0.1, 0.3));
    //Material* grey_diffuse2 = new Lambertian(vec3(0.1, 0.3, 0.1));
    //Material* grey_diffuse3 = new Lambertian(vec3(0.3, 0.1, 0.1));
    Material* grey_diffuse1 = new Transparent(vec3(0,0,0), vec3(0,0,0),vec3(1,1,1), 0,1.32, vec3(1.0,1.0,0.0));
    Material* grey_diffuse2 = new Transparent(vec3(0,0,0), vec3(0,0,0),vec3(1,1,1), 0,1.32,  vec3(1.0,1.0,0.0));
    Material* grey_diffuse3 = new Transparent(vec3(0,0,0), vec3(0,0,0),vec3(1,1,1), 0, 1.32, vec3(1.0,1.0,0.0));
    Material* grey_diffuse4 = new Lambertian(vec3(0.2, 0.2, 0.2));

    Sphere* s1 = new Sphere(vec3(-3,2.3,0), 1.05, 0);
    s1->setMaterial(grey_diffuse1);
    Sphere* s2 = new Sphere(vec3(0,2.3,0), 1.05, 0);
    s2->setMaterial(grey_diffuse2);
    Sphere* s3 = new Sphere(vec3(3,2.3,0), 1.05, 0);
    s3->setMaterial(grey_diffuse3);
    Sphere* s4 = new Sphere(vec3(0,1,3), 0.75, 0);
    s4->setMaterial(grey_diffuse4);

    Material* glass1 = new Transparent(vec3(0,0,0), vec3(0,0,0),vec3(1,1,1), 0,1.7, vec3(1,0.5,0.5));
    Material* glass2 = new Transparent(vec3(0,0,0), vec3(0,0,0),vec3(1,1,1), 0, 1.7, vec3(0.5,1,0.5));
    Material* glass3 = new Transparent(vec3(0,0,0), vec3(0,0,0),vec3(1,1,1), 0, 1.7,vec3(0.5,0.5,1));
    Material* glass4 = new Transparent(vec3(0,0,0), vec3(0,0,0),vec3(1,1,1), 0,vec3(0.8,0.8,0.8));
    Material* glass5 = new Transparent(vec3(0,0,0), vec3(0,0,0),vec3(1,1,1), 0, 1.0,vec3(0.85,0.85,0.85));

    //FittedPlane* t1 = new FittedPlane(vec3(4,15, 0), vec3(0,0,2.1), vec3(2.5,0,0));
    Sphere* t1 = new Sphere(vec3(-3,6.75,0), 1.5, 0);
    t1->setMaterial(glass1);
    Sphere* t2 = new Sphere(vec3(0,6.75,0), 1.5, 0);
    t2->setMaterial(glass2);
    Sphere* t3 = new Sphere(vec3(3,6.75,0), 1.5, 0);
    t3->setMaterial(glass3);
    Sphere* t4 = new Sphere(vec3(0,6,3), 1.5, 0);
    t4->setMaterial(glass4);
    Sphere* t5 = new Sphere(vec3(0,20,0), 4.5, 0);
    t5->setMaterial(glass5);

    scene->objects.push_back(base);
    //scene->objects.push_back(base2);
    scene->objects.push_back(s1);
    scene->objects.push_back(s2);
    scene->objects.push_back(s3);
    //scene->objects.push_back(s4);
    scene->objects.push_back(t1);
    scene->objects.push_back(t2);
    scene->objects.push_back(t3);
    //scene->objects.push_back(t4);
    scene->objects.push_back(t5);


    LightPuntual *light1 = new LightPuntual(
            vec3(0, 50, 0),
            vec3(0.1, 0.1, 0.1),
            vec3(1, 1, 1),
            vec3(0.5, 0.5, 0.5),
            1, 0, 0);

    scene->lights.push_back(light1);
    scene->createSceneBoundaries();
    scene->setAmbientGlobalLight(vec3(0,0,0));
    Render* r = RenderFactory::getInstance()->getRender(RenderFactory::IMAGE);
    r->setCamera(camera);
    r->setScene(scene);

    if(c == 0){
        r->scene_name = "TransparenciesOmbres_Demo1";
        r->startRendering(argc, argv);
    }else if(c == 1){
        r->scene_name = "TransparenciesOmbres_Demo2";
        r->startRendering(argc, argv);
    }else if(c == 2){
        r->scene_name = "TransparenciesOmbres_Demo3";
        r->startRendering(argc, argv);
    }
}


void CustomOnlineScene::startScene2(int argc, char** argv){
    vec3 lookfrom1(0, 10, 10);

    float vfov1 = 60;

    float vfov = vfov1;

    vec3 lookfrom = lookfrom1;

    vec3 lookat(0, 0, 0);
    float dist_to_focus = 4;
    float aperture = 30;
    int pixelsX = 600;
    int pixelsY = 400;



    Camera* camera = new Camera(lookfrom, lookat, vec3(0, 1, 0), vfov, pixelsX, pixelsY, aperture, dist_to_focus);

    Scene* scene = new Scene();
    DataTemplate dt;
    //Base
    FittedPlane* base = new FittedPlane(vec3(0,0,0), vec3(0,0,50), vec3(-50,0,0));
    base->setMaterial(new Lambertian(vec3(1,1,1)-vec3(0.78431, 0.1686, 0.1686)));

    vec3 metal_diffuse = (vec3(0.4, 0.4, 0.4));
    vec3 metal_specular = (vec3(0.9, 0.9, 0.9));
    float shiness = 100;

    Material* metal1 = new Metal(vec3(0,0,0), metal_diffuse, metal_specular, shiness, vec3(0,0,0), 0);
    Material* metal2 = new Metal(vec3(0,0,0), metal_diffuse, metal_specular, shiness, vec3(0,0,0), 0.25);
    Material* metal3 = new Metal(vec3(0,0,0), metal_diffuse, metal_specular, shiness, vec3(0,0,0), 0.5);
    Material* metal4 = new Metal(vec3(0,0,0), metal_diffuse, metal_specular, shiness, vec3(0,0,0), 0.75);
    Material* metal5 = new Metal(vec3(0,0,0), metal_diffuse, metal_specular, shiness, vec3(0,0,0), 1);



    Sphere* s1 = new Sphere(vec3(-5,1,0), 1, 0);
    s1->setMaterial(metal1);
    Sphere* s2 = new Sphere(vec3(-2.5,1,0), 1, 0);
    s2->setMaterial(metal2);
    Sphere* s3 = new Sphere(vec3(0,1,0), 1, 0);
    s3->setMaterial(metal3);
    Sphere* s4 = new Sphere(vec3(2.5,1,0), 1, 0);
    s4->setMaterial(metal4);
    Sphere* s5 = new Sphere(vec3(5,1,0), 1, 0);
    s5->setMaterial(metal5);

    vec3 color = vec3(0.78431, 0.1686, 0.1686);
    Material* color_diffuse1 = new Lambertian(color);
    Material* color_diffuse2 = new Lambertian(color);
    Material* color_diffuse3 = new Lambertian(color);
    Material* color_diffuse4 = new Lambertian(color);
    Material* color_diffuse5 = new Lambertian(color);

    //FittedPlane* t1 = new FittedPlane(vec3(4,15, 0), vec3(0,0,2.1), vec3(2.5,0,0));
    Sphere* t1 = new Sphere(vec3(-5,1,3), 1, 0);
    t1->setMaterial(color_diffuse1);
    Sphere* t2 = new Sphere(vec3(-2.5,1,3), 1, 0);
    t2->setMaterial(color_diffuse2);
    Sphere* t3 = new Sphere(vec3(0,1,3), 1, 0);
    t3->setMaterial(color_diffuse3);
    Sphere* t4 = new Sphere(vec3(2.5,1,3), 1, 0);
    t4->setMaterial(color_diffuse4);
    Sphere* t5 = new Sphere(vec3(5,1,3), 1, 0);
    t5->setMaterial(color_diffuse5);

    scene->objects.push_back(base);
    scene->objects.push_back(s1);
    scene->objects.push_back(s2);
    scene->objects.push_back(s3);
    scene->objects.push_back(s4);
    scene->objects.push_back(s5);
    scene->objects.push_back(t1);
    scene->objects.push_back(t2);
    scene->objects.push_back(t3);
    scene->objects.push_back(t4);
    scene->objects.push_back(t5);

    LightPuntual *light1 = new LightPuntual(
            vec3(0, 50, 0),
            vec3(0.1, 0.1, 0.1),
            vec3(1, 1, 1),
            vec3(0.5, 0.5, 0.5),
            1, 0, 0);

    scene->lights.push_back(light1);
    scene->createSceneBoundaries();
    scene->setAmbientGlobalLight(vec3(0,0,0));
    Render* r = RenderFactory::getInstance()->getRender(RenderFactory::IMAGE);
    r->scene_name = "Metalls_Demo1";
    r->setCamera(camera);
    r->setScene(scene);
    r->startRendering(argc, argv);
}


void CustomOnlineScene::startScene3(int argc, char** argv){
    vec3 lookfrom1(5, 5, 5);

    float vfov1 = 90;

    float vfov = vfov1;

    vec3 lookfrom = lookfrom1;

    vec3 lookat(0, 0, 0);
    float dist_to_focus = 4;
    float aperture = 30;
    int pixelsX = 600;
    int pixelsY = 400;



    Camera* camera = new Camera(lookfrom, lookat, vec3(0, 1, 0), vfov, pixelsX, pixelsY, aperture, dist_to_focus);
    Scene* scene = new Scene();

    FittedPlane* base = new FittedPlane(vec3(0,-2,0), vec3(0,0,50), vec3(-50,0,0));
    base->setMaterial(new Lambertian(vec3(0.1686, 0.1686, 0.78431)));

    vec3 pos1(2,0,-2);
    vec3 pos2(-2,0,2);

    BoundaryObject *bo1 = new BoundaryObject((QString)"://resources/cube.obj", 0);
    BoundaryObject *bo2 = new BoundaryObject((QString)"://resources/cube.obj", 0);
    Translate t1(pos1);
    Translate t2(pos2);

    bo1->aplicaTG(&t1);
    bo2->aplicaTG(&t2);

    vec3 metal_diffuse = (vec3(0.4, 0.4, 0.4));
    vec3 metal_specular = (vec3(0.9, 0.9, 0.9));
    float shiness = 100;

    Material* metal1 = new Metal(vec3(0,0,0), metal_diffuse, metal_specular, shiness, vec3(0,0,0), 0.5);
    Material* metal2 = new Metal(vec3(0,0,0), metal_diffuse, metal_specular, shiness, vec3(0,0,0), 0.5);

    bo1->setMaterial(metal1);
    bo2->setMaterial(metal2);

    scene->objects.push_back(base);
    scene->objects.push_back(bo1);
    scene->objects.push_back(bo2);


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


    scene->lights.push_back(light1);
    scene->lights.push_back(light2);
    scene->lights.push_back(light3);


    scene->createSceneBoundaries();
    scene->setAmbientGlobalLight(vec3(0,0,0));
    Render* r = RenderFactory::getInstance()->getRender(RenderFactory::IMAGE);
    r->scene_name = "ObjectBoundary_Demo1";
    r->setCamera(camera);
    r->setScene(scene);
    r->startRendering(argc, argv);
}


void CustomOnlineScene::startScene4(int argc, char** argv){
    vec3 lookfrom1(0, 5, 5);

    float vfov1 = 90;

    float vfov = vfov1;

    vec3 lookfrom = lookfrom1;

    vec3 lookat(0, 0, 0);
    float dist_to_focus = 4;
    float aperture = 30;
    int pixelsX = 600;
    int pixelsY = 400;

    Camera* camera = new Camera(lookfrom, lookat, vec3(0, 1, 0), vfov, pixelsX, pixelsY, aperture, dist_to_focus);
    Scene* scene = new Scene();

    FittedPlane* base = new FittedPlane(vec3(0,-2,0), vec3(0,0,50), vec3(-50,0,0));
    base->setMaterial(new Lambertian(vec3(0.1686, 0.1686, 0.78431)));

    vec3 pos1(2,0,-2);

    BoundaryObject *bo1 = new BoundaryObject((QString)"://resources/Suzanne.obj", 0);
    //Translate t1(pos1);
    //bo1->aplicaTG(&t1);

    vec3 metal_diffuse = (vec3(0.4, 0.4, 0.4));
    vec3 metal_specular = (vec3(0.9, 0.9, 0.9));
    float shiness = 100;

    Material* metal1 = new Metal(vec3(0,0,0), metal_diffuse, metal_specular, shiness, vec3(0,0,0), 0.5);

    bo1->setMaterial(metal1);

    scene->objects.push_back(base);
    scene->objects.push_back(bo1);


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


    scene->lights.push_back(light1);
    scene->lights.push_back(light2);
    scene->lights.push_back(light3);


    scene->createSceneBoundaries();
    scene->setAmbientGlobalLight(vec3(0,0,0));
    Render* r = RenderFactory::getInstance()->getRender(RenderFactory::ONLINE);
    r->setCamera(camera);
    r->setScene(scene);
    r->startRendering(argc, argv);
}

void CustomOnlineScene::startCovidDataAnimation(int argc, char **argv) {
    vec3 lookfrom(-15, 45, 25);
    float vfov1 = 60;
    float vfov = vfov1;
    vec3 lookat(-15, 0, 20);
    float dist_to_focus = 8;
    float aperture = 30;
    int pixelsX = 600;
    int pixelsY = 400;

    Camera* camera = new Camera(lookfrom, lookat, vec3(0, 1, 0), vfov, pixelsX, pixelsY, aperture, dist_to_focus);


    Scene *s = new Scene();
    s->setDimensions(vec3(-50, -1, -50), vec3(50, 1, 50));
    AnimationDataReader *sc = new AnimationDataReader(s);

    sc->readFile("://resources/total_deaths.txt");


    LightPuntual *light1 = new LightPuntual(
            vec3(2, 20, 20),
            vec3(0.1, 0.1, 0.1),
            vec3(0.6, 0.6, 0.6),
            vec3(0.6, 0.6, 0.6),
            0.7, 0, 0);
    LightPuntual *light2 = new LightPuntual(
            vec3(2, 20, 20),
            vec3(0.1, 0.1, 0.1),
            vec3(2, 2, 2),
            vec3(2, 2, 2),
            0.5, 0, 0);
    LightPuntual *light3 = new LightPuntual(
            vec3(2, 20, 20),
            vec3(0.1, 0.1, 0.1),
            vec3(0.7, 0.7, 0.7),
            vec3(0.7, 0.7, 0.7),
            0.5, 0, 0);

    s->lights.push_back(light1);
    //s->lights.push_back(light2);
    //s->lights.push_back(light3);

    s->setAmbientGlobalLight(vec3(0.1,0.1,0.1));

    Render* r = RenderFactory::getInstance()->getRender(RenderFactory::TEMPORAL);
    r->setCamera(camera);
    r->setScene(s);
    r->startRendering(argc, argv);
}