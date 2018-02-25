#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <Eigen/Dense>
#include "illumination.h"
#include "ray.h"
#include "light.h"
#include "intersect.h"

using namespace Eigen;

class Object
{
public:
    Object(const IlluminationModel&, const std::string&);
    ~Object();
    Vector3f getColor(const IntersectVectors&, const Light&) const;
    Vector3f getAmbient(const Light&) const;
    std::string getName() const;
    virtual float intersect(const Ray&) const = 0;
    virtual void transform(const Matrix4f&) = 0;
    virtual Vector3f getNormal(const Vector3f&) const = 0;
    virtual Vector3f getPos() const = 0;

protected:
    const IlluminationModel *material;
    std::string name;
};

#endif