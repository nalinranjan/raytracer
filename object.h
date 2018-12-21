#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <utility>
#include <Eigen/Dense>
#include "illumination.h"
#include "ray.h"
#include "light.h"
#include "intersect.h"
#include "aabb.h"

using namespace Eigen;

class Object
{
public:
    Object(const IlluminationModel&, float, float, int, float, const std::string&);
    virtual ~Object();
    virtual Vector3f getColor(const Vector3f&, const Light&, const Vector3f&) const = 0;
    virtual Vector3f getAmbient(const Vector3f&, const Light&) const = 0;
    std::string getName() const;
    void print() const;
    const AABB& getAABB() const;
    virtual void makeAABB() = 0;
    virtual float intersect(const Ray&) const = 0;
    virtual void transform(const Matrix4f&) = 0;
    virtual Vector3f getNormal(const Vector3f&) const = 0;
    IntersectVectors getIV(const Vector3f&, const Vector3f&, const Vector3f&) const;
    static Vector3f reflect(const Vector3f&, const Vector3f&);
    static std::pair<Vector3f, bool> transmit(const Vector3f&, const Vector3f&, const float&, const float&);
    virtual Vector3f getPos() const = 0;
    static bool cmpX(const Object *, const Object *);
    static bool cmpY(const Object *, const Object *);
    static bool cmpZ(const Object *, const Object *);
    float getkr() const;
    float getkt() const;
    int getMaxDepth() const;
    float getRefIndex() const;

protected:
    const IlluminationModel *material;
    AABB aabb;
    std::string name;
    float kr, kt, max_depth, ref_index;
};

#endif