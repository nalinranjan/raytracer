#ifndef SPHERE_H
#define SPHERE_H

#include <Eigen/Dense>
#include "object.h"
#include "ray.h"

using namespace Eigen;

class Sphere : public Object
{
public:
    Sphere(const Vector3f&, const Vector3f&, float);
    void transform(const Matrix4f&);
    float intersect(const Ray&) const;
    // Vector3f getPos() const;

private:
    Vector3f center;
    float radius;
};

#endif