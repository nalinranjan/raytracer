#ifndef CHECKERBOARD_NOISY_H
#define CHECKERBOARD_NOISY_H

#include <Eigen/Dense>
#include "triangletex.h"
#include "PerlinNoise.h"
using namespace Eigen;

class CheckerboardNoisy : public TriangleTexture 
{
public:
    CheckerboardNoisy(const Vector2f&, const Vector2f&, const Vector2f&, const Vector3f&, const Vector3f&);
    Vector3f getColor(const Vector3f&) const;
    Vector2f getUV(const Vector3f&) const;

private:
    Vector3f color1, color2;
    PerlinNoise pn;
};

#endif