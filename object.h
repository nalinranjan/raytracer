#ifndef OBJECT_H
#define OBJECT_H

#include <Eigen/Dense>
// #include "color.h"
#include "ray.h"

using namespace Eigen;

class Object
{
public:
    Object(const Vector3f& c);
    void setColor(const Vector3f& c);
    Vector3f getColor() const;
    virtual float intersect(const Ray&) const = 0;
    virtual void transform(const Matrix4f&) = 0;
    // virtual Vector3f getPos() const = 0;

protected:
    Vector3f material;
};

#endif