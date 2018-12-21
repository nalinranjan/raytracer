#ifndef TRIANGLE_TEX_H
#define TRIANGLE_TEX_H

#include <Eigen/Dense>
using namespace Eigen;

class TriangleTexture 
{
public:
    TriangleTexture(const Vector2f&, const Vector2f&, const Vector2f&);
    virtual ~TriangleTexture();
    virtual Vector3f getColor(const Vector3f&) const = 0;

protected:
    Vector2f t1, t2, t3;
};

#endif