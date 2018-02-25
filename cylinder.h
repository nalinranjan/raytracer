#ifndef CYLINDER_H
#define CYLINDER_H

#include <Eigen/Dense>
#include "object.h"
#include "ray.h"
#include "illumination.h"

using namespace Eigen;

class Cylinder : public Object
{
public:
    Cylinder(const Vector3f&, const Vector3f&, float, const IlluminationModel&, const std::string&);
    void transform(const Matrix4f&);
    float intersect(const Ray&) const;
    // Vector3f getColor(const IntersectVectors&, const Light&) const;
    // Vector3f getAmbient(const Light&) const;

private:
    Vector3f centers[2];
    float radius;
};

#endif