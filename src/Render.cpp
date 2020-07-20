#include "Render.h"
#include <future>
#include <iostream>

#define NUM_SAMPLES 100

// Metode Render

// Aquesta funcio transforma cada pixel a coordenades de mon i
// envia un raig des de la camera en aquella direccio cridant al metode CastRay
// i pel pintar la imatge final:
// 1) Neteja la pantalla per a visualitzar el nou frame
// 2) Envia un raig a l'escena per a cada pixel de la pantalla i utilitza el color retornat per a pintar el pixel <- Aquí s'hauria de afegir el numSamples
// 3) Actualitza la sortida corresponent segons la implementació del mètode setPixelColor de cada fill

//Precondicio:
// La Scene ha d'estar creada i inicialitzada

void Render::rendering() {
    std::future<vec3> values[cam->viewportY][cam->viewportX];
    // Recorregut de cada pixel de la imatge final
    for (int y = cam->viewportY - 1; y >= 0; y--) {
        for (int x = 0; x < cam->viewportX; x++) {
            values[y][x] = std::async(&Render::computeAndAssignColor, this, x, y);
            //setPixelColor(computeAndAssignColor(x,y), x, y);
        }
    }
    for (int y = cam->viewportY - 1; y >= 0; y--) {
        printf("%d\n", y);
        for (int x = 0; x < cam->viewportX; x++) {
            setPixelColor(values[y][x].get(), x, y);
        }
    }
}

vec3 Render::computeAndAssignColor(int x, int y) {
    vec3 col(0, 0, 0);
    float u = float(x) / float(cam->viewportX);
    float v = float(y) / float(cam->viewportY);
    for (int i = 1; i <= NUM_SAMPLES; i++) {
        Ray r = cam->getRay(u, v);
        col += scene->ComputeColorRay(r);
    }
    //Truncar valor
    vec3 gammaCorrected = sqrt(col / ((float) NUM_SAMPLES)); //fase 2 gamma correction
    gammaCorrected = vec3(
            glm::min(glm::max(float(0.0), float(gammaCorrected.x)), float(1.0)),
            glm::min(glm::max(float(0.0), float(gammaCorrected.y)), float(1.0)),
            glm::min(glm::max(float(0.0), float(gammaCorrected.z)), float(1.0))
    );
    return gammaCorrected;
}

void Render::exitRender() {
    cleanup();
}

void Render::cleanup() {
    if (scene != NULL) delete scene;
}

// Metode de suport que fa el rendering per a tots els Renders que no usen GLUT
void Render::startRendering(int argc, char **argv) {
    renderingScene();
}

void Render::renderingScene() {
    initRender(this->scene_name + ".ppm");
    rendering();
    exitRender();
}

void Render::setCamera(Camera *c) {
    cam = c;
}

void Render::setScene(Scene *s) {
    scene = s;
}

