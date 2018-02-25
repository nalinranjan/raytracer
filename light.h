#ifndef LIGHT_H
#define LIGHT_H

#include <Eigen/Dense>
using namespace Eigen;

class Light
{
public:
    Light(const Vector3f&, const Vector3f&, const Vector3f&);
    void transform(const Matrix4f&);

    Vector3f color, position, ambient;
};

#endif