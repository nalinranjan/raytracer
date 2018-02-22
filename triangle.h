#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <Eigen/Dense>
#include "object.h"
#include "ray.h"

using namespace Eigen;

class Triangle : public Object
{
public:
    Triangle(const Vector3f&, const Vector3f&, const Vector3f&, const Vector3f&);
    void transform(const Matrix4f&);
    float intersect(const Ray&) const;

private:
    Vector3f vertices[3];
};

#endif