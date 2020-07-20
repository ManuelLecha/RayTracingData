#include "Cara.h"
#include <cmath>

Cara::Cara() {
    normal.x = 0.0;
    normal.y = 0.0;
    normal.z = 0.0;
}

Cara::Cara(int i1, int i2, int i3, int i4) {
    idxVertices.push_back(i1);
    idxVertices.push_back(i2);
    idxVertices.push_back(i3);
    if (i4 != -1) idxVertices.push_back(i4);
}


void Cara::calculaNormal(vector<Vertices> &v) {
    vec4 v0 = v[idxVertices[0]];
    vec4 v1 = v[idxVertices[1]];
    vec4 v2 = v[idxVertices[2]];

    vec3 t1(v1.x - v0.x, v1.y-v0.y, v1.z - v0.z);
    vec3 t2(v2.x - v0.x, v2.y-v0.y, v2.z - v0.z);

    normal = glm::normalize(glm::cross(t1, t2));
}

bool Cara::intersection(const Ray &r, float t_min, float t_max, IntersectionInfo &info, const vector<vec4> &vertexs,
                        const Material *material) const {
    if (this->idxVertices.size() == 3) {
        return intersectionTriangle(r, t_min, t_max, info, vertexs, material);
    } else {
        return intersectionQuadrilateral(r, t_min, t_max, info, vertexs, material);
    }
}

bool
Cara::intersectionTriangle(const Ray &r, float t_min, float t_max, IntersectionInfo &info, const vector<vec4> &vertexs,
                           const Material *material) const {
    float tol = 10e-6; //Per càlcul d'igualtats amb floats

    if (dot(r.dirVector(), normal) == 0) {
        return false;
    }

    vec4 point1 = vertexs[idxVertices[0]];
    vec4 point2 = vertexs[idxVertices[1]];
    vec4 point3 = vertexs[idxVertices[2]];

    vec3 v1 = vec3(point1.x, point1.y, point1.z);
    vec3 v2 = vec3(point2.x, point2.y, point2.z);
    vec3 v3 = vec3(point3.x, point3.y, point3.z);

    float d = -normal[0] * v1[0] - normal[1] * v1[1] - normal[2] * v1[2];
    vec3 rp = r.initialPoint();
    vec3 vp = r.dirVector();
    float temp = -normal[0] * rp[0] - normal[1] * rp[1] - normal[2] * rp[2] - d;

    temp /= normal[0] * vp[0] + normal[1] * vp[1] + normal[2] * vp[2];

    // Retornem false si no estem en el rang demanat
    if (temp > t_max || temp < t_min) {
        return false;
    }

    // Omplim el camp de info:

    info.t = temp;
    info.p = r.pointAtParameter(info.t);

    // La normal a un pla es la mateixa per tots els punts
    info.normal = normal;
    info.mat_ptr = material;

    //INTERSECCIÓ PLA FETA, ARA FALTA INTERSECCIÓ TRIANGLE

    //És vertex
    if (distance(v1, info.p) < tol)
        return true;
    if (distance(v2, info.p) < tol)
        return true;
    if (distance(v3, info.p) < tol)
        return true;
    //No és vèrtex, aconseguim coordenades baricentriques
    double angle, base, height;
    vec3 baseNormalized, heightNormalized;

    //Calcul big area
    baseNormalized = normalize(v2 - v1);
    heightNormalized = normalize(v3 - v1);
    angle = acos(dot(baseNormalized, heightNormalized));
    base = distance(v1, v2);
    height = distance(v1, v3) * sin(angle);

    double bigArea = (base * height) / 2.0;

    // Calcul u

    baseNormalized = normalize(v1 - info.p);
    heightNormalized = normalize(v2 - info.p);
    angle = acos(dot(baseNormalized, heightNormalized));
    base = distance(info.p, v1);
    height = distance(info.p, v2) * sin(angle);

    double u = (((base * height) / 2.0) / bigArea);

    //Calcul v

    baseNormalized = normalize(v2 - info.p);
    heightNormalized = normalize(v3 - info.p);
    angle = acos(dot(baseNormalized, heightNormalized));
    base = distance(info.p, v2);
    height = distance(info.p, v3) * sin(angle);

    double v = (((base * height) / 2.0) / bigArea);

    //Calcul w

    baseNormalized = normalize(v3 - info.p);
    heightNormalized = normalize(v1 - info.p);
    angle = acos(dot(baseNormalized, heightNormalized));
    base = distance(info.p, v3);
    height = distance(info.p, v1) * sin(angle);

    double w = (((base * height) / 2.0) / bigArea);

    //Getting barycentric coordinates
    vec3 pBaricentricCoordinates = vec3(u, v, w);

    //Is point inside
    bool xInequality = 0 < pBaricentricCoordinates.x && pBaricentricCoordinates.x < 1;
    bool yInequality = 0 < pBaricentricCoordinates.y && pBaricentricCoordinates.y < 1;
    bool zInequality = 0 < pBaricentricCoordinates.z && pBaricentricCoordinates.z < 1;
    bool sumCoordIsOne =
            abs(1 - (pBaricentricCoordinates.x + pBaricentricCoordinates.y + pBaricentricCoordinates.z)) < tol;
    if (sumCoordIsOne && xInequality && yInequality && zInequality)
        return true;
    return false;
}

bool Cara::intersectionQuadrilateral(const Ray &r, float t_min, float t_max, IntersectionInfo &info,
                                     const vector<vec4> &vertexs, const Material *material) const {
    return true;
}



