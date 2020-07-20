#include "Triangle.h"

Triangle::Triangle(vec3 v1, vec3 v2, vec3 v3, float v) : PlaneFigure(cross(v2 - v1, v3 - v1), v1, v) {
    this->simplex = new Simplex(v1, v2, v3);
}

bool Triangle::intersection(const Ray &r, float t_min, float t_max, IntersectionInfo &info) const {
    if (getPlaneContaining()->intersection(r, t_min, t_max, info)) {
        info.mat_ptr = this->material;
        if (pIsVertex(info.p)) {
            return true;
        }
        return isPointInside(getBaricentricCoordinates(info.p));
    }
    return false;
}

const vec3 Triangle::getBaricentricCoordinates(const vec3 &p) const {
    double bigArea = this->simplex->calculateTriangleArea();
    double u = (Simplex(p, this->simplex->getV1(), this->simplex->getV2()).calculateTriangleArea()) / bigArea;
    double v = (Simplex(p, this->simplex->getV2(), this->simplex->getV3()).calculateTriangleArea()) / bigArea;
    double w = (Simplex(p, this->simplex->getV3(), this->simplex->getV1()).calculateTriangleArea()) / bigArea;
    return vec3(u, v, w);
}

void Triangle::aplicaTG(TG *t) {
    if (dynamic_cast<Translate *>(t)) {
        // Per ara només es preveuen translacions

        vec4 v1_aux(simplex->getV1(), 1.0);
        vec4 v2_aux(simplex->getV2(), 1.0);
        vec4 v3_aux(simplex->getV3(), 1.0);

        v1_aux = t->getTG() * v1_aux;
        v2_aux = t->getTG() * v2_aux;
        v3_aux = t->getTG() * v3_aux;

        vec3 v1(v1_aux.x, v1_aux.y, v1_aux.z);
        vec3 v2(v2_aux.x, v2_aux.y, v2_aux.z);
        vec3 v3(v3_aux.x, v3_aux.y, v3_aux.z);


        delete (this->simplex);

        this->simplex = new Simplex(v1, v2, v3);
    }
}

Triangle::~Triangle() {
    delete (this->simplex);
}

bool Triangle::isPointInside(const vec3 &pBaricentricCoordinates) const {
    float tol = 10e-6;
    bool xInequality = 0 < pBaricentricCoordinates.x && pBaricentricCoordinates.x < 1;
    bool yInequality = 0 < pBaricentricCoordinates.y && pBaricentricCoordinates.y < 1;
    bool zInequality = 0 < pBaricentricCoordinates.z && pBaricentricCoordinates.z < 1;
    bool sumCoordIsOne =
            abs(1 - (pBaricentricCoordinates.x + pBaricentricCoordinates.y + pBaricentricCoordinates.z)) < tol;
    return sumCoordIsOne && xInequality && yInequality && zInequality;
}

bool Triangle::pIsVertex(const vec3 &p) const {
    float tol = 10e-6;
    vec3 v1 = this->simplex->getV1();
    vec3 v2 = this->simplex->getV2();
    vec3 v3 = this->simplex->getV3();
    if (distance(v1, p) < tol)
        return true;
    if (distance(v2, p) < tol)
        return true;
    return distance(v3, p) < tol;
}

Parallelepiped Triangle::getBoundaries() {
    vec3 pmin = vec3(
            min(min(simplex->getV1().x, simplex->getV2().x), simplex->getV3().x),
            min(min(simplex->getV1().y, simplex->getV2().y), simplex->getV3().y),
            min(min(simplex->getV1().z, simplex->getV2().z), simplex->getV3().z)
    );
    vec3 pmax = vec3(
            max(max(simplex->getV1().x, simplex->getV2().x), simplex->getV3().x),
            max(max(simplex->getV1().y, simplex->getV2().y), simplex->getV3().y),
            max(max(simplex->getV1().z, simplex->getV2().z), simplex->getV3().z)
    );
    return Parallelepiped(pmin, pmax);
}

void Triangle::translate(vec3 translation) {
    vec3 v1 = simplex->getV1();
    vec3 v2 = simplex->getV2();
    vec3 v3 = simplex->getV3();

    v1 += translation;
    v2 += translation;
    v3 += translation;

    delete (this->simplex);
    this->simplex = new Simplex(v1, v2, v3);

}

void Triangle::scale(double r) {
    vec3 v1 = simplex->getV1();
    vec3 v2 = simplex->getV2();
    vec3 v3 = simplex->getV3();
    vec3 center = (v1 + v2 + v3) / 3.0f;

    v1 = (v1 - center) * (float) r + center;
    v2 = (v2 - center) * (float) r + center;
    v3 = (v3 - center) * (float) r + center;

    delete (this->simplex);
    this->simplex = new Simplex(v1, v2, v3);
}