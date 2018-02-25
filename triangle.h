#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <Eigen/Dense>
#include "object.h"
#include "ray.h"
#include "illumination.h"

using namespace Eigen;

class Triangle : public Object
{
public:
    Triangle(const Vector3f&, const Vector3f&, const Vector3f&, const IlluminationModel&, const std::string&);
    void transform(const Matrix4f&);
    float intersect(const Ray&) const;
    Vector3f getNormal(const Vector3f&) const;
    // Vector3f getColor(const IntersectVectors&, const Light&) const;
    // Vector3f getAmbient(const Light&) const;

private:
    Vector3f vertices[3];
};

#endif