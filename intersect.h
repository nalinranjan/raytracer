#ifndef INTERSECT_H
#define INTERSECT_H

#include <Eigen/Dense>
using namespace Eigen;

class IntersectVectors
{
public:
    IntersectVectors(const Vector3f&, const Vector3f&, const Vector3f&, const Vector3f&, const Vector3f&);
    Vector3f S, V, N, H, R;
};

#endif