#ifndef RAY_H
#define RAY_H

#include <Eigen/Dense>

using namespace Eigen;

class Ray
{
public:
    Ray(const Vector3f&, const Vector3f&);
    Vector3f origin, direction;    
};

#endif