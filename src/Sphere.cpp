#include "Sphere.h"
#include "AnimationDataReader.h"

Sphere::Sphere(vec3 cen, float r, float d) : Object(d) {
    center = cen;
    radius = r;
}

bool Sphere::intersection(const Ray &ray, float t_min, float t_max, IntersectionInfo &info) const {

    vec3 oc = ray.initialPoint() - center;
    float a = dot(ray.dirVector(), ray.dirVector());
    float b = dot(oc, ray.dirVector());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;

    if (discriminant > 0) {
        float t1 = (-b - sqrt(discriminant)) / a;
        float t2 = (-b + sqrt(discriminant)) / a;

        if (t1 < t_max && t1 > t_min) {

            if (t2 < t_max && t2 > t_min) {
                info.t = glm::min(t1, t2);
                info.p = ray.pointAtParameter(info.t);
                info.normal = (info.p - center) / radius;
                info.mat_ptr = material;
                info.d = distance(ray.pointAtParameter(t1), ray.pointAtParameter(t2));
                return true;
            }

            info.t = t1;
            info.p = ray.pointAtParameter(info.t);
            info.normal = (info.p - center) / radius;
            info.mat_ptr = material;
            info.d = 0;
            return true;
        }
        if (t2 < t_max && t2 > t_min) {
            info.t = t2;
            info.p = ray.pointAtParameter(info.t);
            info.normal = (info.p - center) / radius;
            info.mat_ptr = material;
            info.d = 0;
            return true;
        }
    }

    return false;
}

void Sphere::aplicaTG(TG *t) {
    AnimationDataTG* dtg;
    if( (dtg = dynamic_cast<AnimationDataTG*>(t))){
        this->radius = dtg->value;
        return;
    }
    vec4 c(center, 1.0);
    vec4 vr(this->radius, 0, 0, 0);
    mat4 tgmat = t->getTG();
    c = tgmat*c;
    vr = tgmat*vr;
    center.x = c.x;
    center.y = c.y;
    center.z = c.z;
    radius = glm::length(vr);
}

Parallelepiped Sphere::getBoundaries() {
    vec3 radiusVector = vec3(radius, radius, radius);
    vec3 pmin = center - radiusVector;
    vec3 pmax = center + radiusVector;
    return Parallelepiped(pmin, pmax);
}

