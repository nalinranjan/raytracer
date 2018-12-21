#ifndef PHONG_H
#define PHONG_H

#include <Eigen/Dense>
#include "illumination.h"
#include "intersect.h"
#include "light.h"
using namespace Eigen;

class Phong : public IlluminationModel 
{
public:
    Phong(const Vector3f&, const Vector3f&, const Vector3f&, float);
    Vector3f getColor(const IntersectVectors&, const Light&, const Vector3f& = {}) const;
    Vector3f getAmbient(const Light&, const Vector3f& = {}) const;

private:
    Vector3f ka, kd, ks;
    float ke;
};

#endif