#include "trytexture.h"
#include <cmath>

TryTexture::TryTexture(const Vector2f& t1, const Vector2f& t2, const Vector2f& t3):
    TriangleTexture(t1, t2, t3)
{
}

Vector3f TryTexture::getColor(const Vector3f& barycentric) const
{
    Vector2f uv = getUV(barycentric);
    float n = (1 + sin(((uv.x() + uv.y())/2 + pn.noise(uv.x()*5, uv.y()*5, 1.0) / 2.0) * 50)) / 2.0;
    return Vector3f(n/5, n/1.5, n/2.5);
}

Vector2f TryTexture::getUV(const Vector3f& barycentric) const
{
    Vector2f t = barycentric.x()*t1 + barycentric.y()*t2 + barycentric.z()*t3;
    return t;
}