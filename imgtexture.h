#ifndef IMG_TEXTURE_H
#define IMG_TEXTURE_H

#include <Eigen/Dense>
#include <pngwriter.h>
#include "triangletex.h"
#include "params.h"
using namespace Eigen;

class ImgTexture : public TriangleTexture 
{
public:
    ImgTexture(const Vector2f&, const Vector2f&, const Vector2f&, const char *);
    ~ImgTexture();
    Vector3f getColor(const Vector3f&) const;
    Vector2f getUV(const Vector3f&) const;

private:
    pngwriter img;
    float uMult, vMult;
};

#endif