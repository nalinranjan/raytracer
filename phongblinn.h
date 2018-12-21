#ifndef PHONG_BLINN_H
#define PHONG_BLINN_H

#include <Eigen/Dense>
#include "illumination.h"
#include "intersect.h"
#include "light.h"
#include "triangletex.h"
using namespace Eigen;

class PhongBlinn : public IlluminationModel 
{
public:
    PhongBlinn(const Vector3f&, const Vector3f&, const Vector3f&, float, const TriangleTexture *);
    ~PhongBlinn();
    Vector3f getColor(const IntersectVectors&, const Light&, const Vector3f& = {}) const;
    Vector3f getAmbient(const Light&, const Vector3f& = {}) const;

private:
    const TriangleTexture *texture;
    Vector3f ka, kd, ks;
    float ke;
};

#endif