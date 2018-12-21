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
    Triangle(const Vector3f&, const Vector3f&, const Vector3f&, const IlluminationModel&, float, float, int, float, const std::string& = "");
    void makeAABB();
    void transform(const Matrix4f&);
    float intersect(const Ray&) const;
    Vector3f getNormal(const Vector3f&) const;
    Vector3f getBarycentric(const Vector3f&) const;
    Vector3f getColor(const Vector3f&, const Light&, const Vector3f&) const;
    Vector3f getAmbient(const Vector3f&, const Light&) const;
    Vector3f getPos() const;

private:
    Vector3f vertices[3], vec0, vec1;
    float d00, d01, d11, invDenom;
};

#endif