#ifndef TRY_TEXTURE_H
#define TRY_TEXTURE_H

#include <Eigen/Dense>
#include "triangletex.h"
#include "PerlinNoise.h"
using namespace Eigen;

class TryTexture : public TriangleTexture 
{
public:
    TryTexture(const Vector2f&, const Vector2f&, const Vector2f&);
    Vector3f getColor(const Vector3f&) const;
    Vector2f getUV(const Vector3f&) const;

private:
    PerlinNoise pn;
};

#endif