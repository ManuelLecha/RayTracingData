//
// Created by Manuel Lecha Sánchez on 02/03/2020.
//

#include "Cylinder.h"
#include <math.h>
#include "AnimationDataReader.h"

Cylinder::Cylinder(vec3 center, float radius, float height, float v) : Object(v) {
    this->center = center;
    this->radius = radius;
    this->height = height;

    vec3 topDiskOrientation(0.0, 1.0, 0.0);
    vec3 bottomDiskOrientation(0.0, -1.0, 0.0);

    this->topDisk = new Disk(topDiskOrientation, center + vec3(0, height, 0), radius);
    this->bottomDisk = new Disk(bottomDiskOrientation, center, radius);
}

//Last modification to return the distance between the two possible intersection points
bool Cylinder::intersection(const Ray &r, float t_min, float t_max, IntersectionInfo &info) const {

    float t = -1.0;
    IntersectionInfo aux;

    if (topDisk->intersection(r, t_min, t_max, aux)) {
        t = info.t;
    }

    if (bottomDisk->intersection(r, t_min, t_max, aux)) {
        if (t > 0) {

            info.d = distance(r.pointAtParameter(t), r.pointAtParameter(info.t));
            info.t = glm::min(t, info.t);
            info.p = r.pointAtParameter(info.t);
            info.mat_ptr = this->material;
            return true;

        } else {
            t = info.t;
        }
    }

    //supposing dir vector is normalized
    float a = r.origin.x - center.x;
    float b = r.origin.z - center.z;
    float dx = r.direction.x;
    float dz = r.direction.z;
    float dirsqnorm = pow(dx, 2) + pow(dz, 2);
    float delta = dirsqnorm * pow(radius, 2) - pow((b * dx - a * dz), 2);


    if (delta >= 0) {

        float aux = -(a * dx + b * dz);
        float temp = (aux + sqrt(delta)) / dirsqnorm;

        if (temp > t_min && r.pointAtParameter(temp).y < topDisk->center.y && r.pointAtParameter(temp).y > center.y) {

            if (t > 0) {

                info.d = distance(r.pointAtParameter(t), r.pointAtParameter(temp));
                info.t = glm::min(t, temp);
                info.p = r.pointAtParameter(info.t);
                info.mat_ptr = material;
                info.normal = normalize(info.p - (center + info.p.y));
                return true;

            } else {
                t = temp;
            }
        }

        if (delta > 0) {

            temp = (aux - sqrt(delta)) / dirsqnorm;

            if (temp > t_min && r.pointAtParameter(temp).y < topDisk->center.y && r.pointAtParameter(temp).y > center.y) {

                if (t > 0) {

                    info.d = distance(r.pointAtParameter(t), r.pointAtParameter(temp));
                    info.t = glm::min(t, temp);
                    info.p = r.pointAtParameter(info.t);
                    info.mat_ptr = material;
                    info.normal = normalize(info.p - (center + info.p.y));
                    return true;

                } else {

                    t = temp;

                }
            }
        }
    }

    if (t > 0) {

        info.t = t;
        info.p = r.pointAtParameter(info.t);
        info.mat_ptr = material;
        info.normal = normalize(info.p - (center + info.p.y));
        info.d = 0;
        return true;

    }else{
        return false;
    }


}

void Cylinder::aplicaTG(TG *t) {
    AnimationDataTG* dtg;
    if( (dtg = dynamic_cast<AnimationDataTG*>(t))){
        this->height = dtg->value;
        return;
    }

    vec4 c(center, 1.0);
    c = t->getTG() * c;
    center.x = c.x;
    center.y = c.y;
    center.z = c.z;

    vec4 rv = vec4(radius, 0, 0, 0);
    vec4 hv = vec4(0, height, 0, 0);

    rv = t->getTG() * rv;
    hv = t->getTG() * hv;
    radius = glm::length(rv);
    height = glm::length(hv);
}

Cylinder::~Cylinder() {

}

Parallelepiped Cylinder::getBoundaries() {
    vec3 minp = center - vec3(radius, 0.0, radius);
    vec3 maxp = center + vec3(radius, height, radius);
    return Parallelepiped(minp, maxp);
}