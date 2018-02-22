#ifndef CYLINDER_H
#define CYLINDER_H

#include <Eigen/Dense>
#include "object.h"

using namespace Eigen;

class Cylinder : public Object
{
public:
    Cylinder(const Vector3f&, const Vector3f&, const Vector3f&, float);
    void transform(const Matrix4f&);
    float intersect(const Ray &) const;

private:
    Vector3f centers[2];
    float radius;
};

#endif