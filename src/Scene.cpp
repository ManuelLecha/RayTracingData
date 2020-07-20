#include "Scene.h"
#include <math.h>
#include <iostream>
#include "Transparent.h"

#define MAXDEPTH 13
#define EPSILON_ACNE 0.01
#define DMAXTRANSPARENCY 1.0

Scene::Scene() {
    pmin.x = -0.5f;
    pmin.y = -0.5f;
    pmin.z = -0.5f;
    pmax.x = 0.5f;
    pmax.y = 0.5f;
    pmax.z = 0.5f;
}

Scene::~Scene() {
// TODO Fase 1: Quan s'incloguin nous objectes, cal retocar aquest destructor
    for (unsigned int i = 0; i < objects.size(); ++i) {
        if (objects[i]) {
            if (dynamic_cast<Sphere *>(objects[i]))
                delete (Sphere *) (objects[i]);
        }
    }
}

/*
** Si un objecte es intersecat pel raig, el parametre  de tipus IntersectInfo conte
** la informació sobre la interesccio.
** El metode retorna true si algun objecte es intersecat o false en cas contrari.
**
*/

bool Scene::intersection(const Ray &raig, float t_min, float t_max, IntersectionInfo &info) const {

    std::vector<Object *> objects = this->objects;
    IntersectionInfo auxInfo;
    float min_t = FLT_MAX;
    vec3 og = raig.origin;
    bool intersects = false;

    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->intersection(raig, t_min, t_max, auxInfo)) {
            if (auxInfo.t > 0 && auxInfo.t < min_t) {
                intersects = true;
                info = auxInfo;
                min_t = auxInfo.t;
            }
        }
    }

    return intersects;
}


vec3 Scene::ComputeColorRay(Ray &ray) {

    vec3 zeroColor = vec3(0, 0, 0);
    IntersectionInfo info;
    vec3 color = intersection(ray, MIN_T_INTERSECTION, FLT_MAX, info) ?
                 getObjectIntersectionColor(ray, info, 0) : getBackgroundColor(ray);
    return color;

}

vec3 Scene::getObjectIntersectionColor(Ray &ray, IntersectionInfo &intersectionInfo, int depth) {
    //return intersectionInfo.normal; //Fase 0 normal
    //return intersectionInfo.mat_ptr->diffuse; //Fase 2 apartat 1
    std::vector<Ray> r_out;
    std::vector<vec3> attenuation_colors;
    vec3 blinnPhong = Blinn_Phong(ray, intersectionInfo);
    vec3 colorToReturn;
    vec3 scatterColor = vec3(0.0, 0.0, 0.0);
    const Material *material = intersectionInfo.mat_ptr;
    //First we correct the initial point for the scatter
    if (depth < MAXDEPTH) {
        IntersectionInfo recursiveInfo;
        if (material->scatter(ray, intersectionInfo, attenuation_colors, r_out)) {
            vec3 attenuation_color;
            Ray rayGenerated;
            for (int i = 0; i < r_out.size(); i++) {
                rayGenerated = r_out.at(i);
                attenuation_color = attenuation_colors.at(i);
                if (intersection(rayGenerated, EPSILON_ACNE, FLT_MAX,
                                 recursiveInfo)) { //EPSILON_ACNE to correct the acne in reflection
                    //First we check if the intersection is with the same object at the same point due to math error approximation
                    scatterColor += attenuation_color *
                                    getObjectIntersectionColor(rayGenerated, recursiveInfo, depth + 1);
                } else {
                    scatterColor += attenuation_color * this->getBackgroundColor(ray);
                }
            }
        scatterColor = scatterColor/(float(r_out.size()));
        }
        colorToReturn = blinnPhong + scatterColor;
    } else {
        colorToReturn = blinnPhong;
    }
    return colorToReturn;
}

vec3 Scene::getBackgroundColor(Ray &ray) {
    vec3 ray2 = normalize(ray.direction);
    return vec3(0.4,0.4,0.2);
}

void Scene::update(int nframe) {
    for (unsigned int i = 0; i < objects.size(); i++) {
        if (dynamic_cast<Animable *>(objects[i])) objects[i]->update(nframe);
    }
}

void Scene::setMaterials(ColorMap *cm) {

    // AIXO HO CONTROLA TOT DATAREADER, LA NOSTRE SCENE NO SAP RES DE COLORMAPS.

    /*
    Material *m;
    // Fase 0
    // Cal canviar el codi per a afegir més materials.

    // Fase 2
    // Cal canviar el tipus de material Lambertian, Specular, Transparent, Tipus Textura
    if (cm == nullptr)
        m = new Lambertian(vec3(0.5, 0.2, 0.7));
    else {
        // Fase 2:
        //  Crear els materials segons la paleta de cada propietat a cada objecte de l'escena
        m = new Lambertian(cm->getColor(0));
    }
    for (auto o:objects)
        if (o->getMaterial()== nullptr) o->setMaterial(m);*/
}

void Scene::setDimensions(vec3 p1, vec3 p2) {
    pmin = p1;
    pmax = p2;
}

void Scene::createSceneBoundaries() {
    float x_min, y_min, z_min, x_max, y_max, z_max;
    x_min = FLT_MAX;
    y_min = FLT_MAX;
    z_min = FLT_MAX;
    x_max = FLT_MIN;
    y_max = FLT_MIN;
    z_max = FLT_MIN;
    for (Object *gObject : this->objects) {
        Parallelepiped minPar = gObject->getBoundaries();
        vec3 pmin = minPar.getPmin();
        vec3 pmax = minPar.getPmax();
        if (x_min > pmin.x)
            x_min = pmin.x;
        if (y_min > pmin.y)
            y_min = pmin.y;
        if (z_min > pmin.z)
            z_min = pmin.z;
        if (x_max < pmax.x)
            x_max = pmax.x;
        if (y_max < pmax.y)
            y_max = pmax.y;
        if (z_max < pmax.z)
            z_max = pmax.z;
    }
    this->setDimensions(vec3(x_min, y_min, z_min), vec3(x_max, y_max, z_max));
}


vec3 Scene::Blinn_Phong(Ray &ray, IntersectionInfo &info) {

    vec3 c = (info.mat_ptr->ambient) * (this->ambientGlobalLight); //Global light in the sum
    for (Light *l: lights) {
        vec3 L = normalize(l->computeLightDirection(info.p));
        vec3 V = normalize(ray.origin - info.p);
        vec3 H = normalize(L + V);

        float att = l->computeAttenuation(info.p);
        vec3 shadowFactor = getShadowFactor(info.p, l, L);
        //float shadowFactor = 1;


        vec2 planeCoords = vec2(0, 0);
        if (basePlane != nullptr) {
            planeCoords = basePlane->projectPlane(info.p);
            planeCoords.y *= -1;
            planeCoords += vec2(1, 1);
            planeCoords /= 2;
            if (planeCoords.x < 0)planeCoords.x = 0;
            if (planeCoords.y < 0)planeCoords.y = 0;
            if (planeCoords.x > 1)planeCoords.x = 1;
            if (planeCoords.y > 1)planeCoords.y = 1;
        }

        //LA PARTE DE LAS COORDENADAS DE UNA TEXTURA NO ES NADA GENERICO. PERO ES EL PROBLEMA DEL DISEÑO QUE NOS DAN.
        //SI NOS SOBRA TIEMPO, PODEMOS MAPPEAR TEXTURAS A MAS DE UN OBJETO DISTINTO, Y ENTOCES SI QUE SE TIENE QUE GENERALIZAR

        vec3 surfaceNormal = glm::normalize(info.normal);
        vec3 ambientComponent = (info.mat_ptr->ambient) * (l->ambient);
        //vec3 diffuseComponent = (info.mat_ptr->diffuse)*(l->diffuse)*glm::max(dot(L,info.normal),0.0f);
        vec3 diffuseComponent = info.mat_ptr->getDiffuse(planeCoords) * (l->diffuse) * glm::max(dot(L, surfaceNormal), 0.0f);
        vec3 specularComponent = (info.mat_ptr->specular) * (l->specular) *
                                 pow(glm::max(dot(H, surfaceNormal), 0.0f), info.mat_ptr->shininess);

        c += ambientComponent + shadowFactor * att * (diffuseComponent + specularComponent);
    }
    return c;
}

std::vector<IntersectionInfo> Scene::multipleIntersection(const Ray &raig, float t_min, float t_max) const {
    std::vector<Object *> objects = this->objects;
    std::vector<IntersectionInfo> infos;
    for (int i = 0; i < objects.size(); i++) {
        IntersectionInfo auxInfo;
        if (objects[i]->intersection(raig, t_min, t_max, auxInfo)) {
            infos.push_back(auxInfo);
        }
    }
    std::sort(infos.begin(), infos.end());
    return infos;
}

vec3 Scene::getShadowFactor(vec3 intersectionPoint, Light *l, vec3 PL) {
    IntersectionInfo info;
    float epsilon = 0.01;
    vec3 p0Corrected = intersectionPoint + epsilon * PL;
    Ray lightRay(p0Corrected, PL); //Ray to light using the previous calculation
    std::vector<IntersectionInfo> infos = multipleIntersection(lightRay, MIN_T_INTERSECTION, FLT_MAX);
    int i = 0;
    vec3 sFactor(1,1,1);

    while (i < infos.size()) {
        if (const Transparent *t = dynamic_cast<const Transparent *>(infos[i].mat_ptr)) {
            vec3 dTransparency = colorTransparency(infos[i].mat_ptr->transparency, infos[i].d);
            sFactor = sFactor*dTransparency;
        } else {
            return vec3(0,0,0);
        }
        i = i + 1;
    }
    sFactor.x = glm::max(sFactor.x, 0.0f);
    sFactor.y = glm::max(sFactor.y, 0.0f);
    sFactor.z = glm::max(sFactor.z, 0.0f);

    return sFactor;
}

void Scene::setAmbientGlobalLight(vec3 value) {
    this->ambientGlobalLight = value;
}
