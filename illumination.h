#ifndef ILLUMINATION_H
#define ILLUMINATION_H

#include <Eigen/Dense>
#include "intersect.h"
#include "light.h"
using namespace Eigen;

class IlluminationModel
{
public:
    IlluminationModel();
    virtual ~IlluminationModel();
    virtual Vector3f getColor(const IntersectVectors&, const Light&, const Vector3f& = {}) const = 0;
    virtual Vector3f getAmbient(const Light&, const Vector3f& = {}) const = 0;
};

#endif