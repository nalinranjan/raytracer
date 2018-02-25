#ifndef SPHERE_H
#define SPHERE_H

#include <Eigen/Dense>
#include "object.h"
#include "ray.h"
#include "illumination.h"

using namespace Eigen;

class Sphere : public Object
{
public:
    Sphere(const Vector3f&, float, const IlluminationModel&, const std::string&);
    void transform(const Matrix4f&);
    float intersect(const Ray&) const;
    Vector3f getNormal(const Vector3f&) const;
    // Vector3f getColor(const IntersectVectors&, const Light&) const;
    // Vector3f getAmbient(const Light&) const;
    // Vector3f getPos() const;

private:
    Vector3f center;
    float radius;
};

#endif