#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <Eigen/Dense>
#include "triangletex.h"
using namespace Eigen;

class Checkerboard : public TriangleTexture 
{
public:
    Checkerboard(const Vector2f&, const Vector2f&, const Vector2f&, const Vector3f&, const Vector3f&);
    Vector3f getColor(const Vector3f&) const;
    Vector2f getUV(const Vector3f&) const;

private:
    Vector3f color1, color2;
};

#endif