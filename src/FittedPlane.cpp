#include "include/FittedPlane.h"

FittedPlane::FittedPlane(vec3 center, vec3 up, vec3 right) : Plane(glm::normalize(glm::cross(up, -right)), center, -1) {
    this->center = center;
    this->upLength = glm::length(up);
    this->rightLength = glm::length(right);
    this->up = glm::normalize(up);
    this->right = glm::normalize(right);
}

bool FittedPlane::intersection(const Ray &r, float t_min, float t_max, IntersectionInfo &info) const {
    IntersectionInfo tmp_info;


    if (Plane::intersection(r, t_min, t_max, tmp_info)) {
        vec3 ip = tmp_info.p;
        vec3 cp = ip - center;
        float ul = glm::dot(cp, up);
        float rl = glm::dot(cp, right);
        if (-upLength <= ul && ul <= upLength && -rightLength <= rl && rl <= rightLength) {
            info = tmp_info;
            return true;
        }
    }
    return false;
}

Parallelepiped FittedPlane::getBoundaries() {
    vec3 q[4];
    q[0] = center + up * upLength + right * rightLength;
    q[1] = center + up * upLength - right * rightLength;
    q[2] = center - up * upLength + right * rightLength;
    q[3] = center - up * upLength - right * rightLength;
    vec3 minP = center;
    vec3 maxP = center;
    for (vec3 p: q) {
        if (p.x < minP.x)minP.x = p.x;
        if (p.y < minP.y)minP.y = p.y;
        if (p.z < minP.z)minP.z = p.z;
        if (p.x > maxP.x)maxP.x = p.x;
        if (p.y > maxP.y)maxP.y = p.y;
        if (p.z > maxP.z)maxP.z = p.z;
    }

    return Parallelepiped(minP, maxP);
}

vec2 FittedPlane::projectPlane(vec3 point) {
    vec3 pc = point - center;
    vec3 tn = normal * glm::dot(pc, normal);
    vec3 projPoint = point - tn;
    vec3 pvec = projPoint - center;
    float ul = glm::dot(pvec, up);
    float rl = glm::dot(pvec, right);
    return vec2(rl / rightLength, ul / upLength);
}

vec2 FittedPlane::getUVFromSurfacePoint(vec3 point){
    vec2 planeCoords = projectPlane(point);
    planeCoords.y *= -1;
    planeCoords += vec2(1, 1);
    planeCoords /= 2;
    if (planeCoords.x < 0)planeCoords.x = 0;
    if (planeCoords.y < 0)planeCoords.y = 0;
    if (planeCoords.x > 1)planeCoords.x = 1;
    if (planeCoords.y > 1)planeCoords.y = 1;
    return planeCoords;
}
