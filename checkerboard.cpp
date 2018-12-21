#include "checkerboard.h"

Checkerboard::Checkerboard(const Vector2f& t1, const Vector2f& t2, const Vector2f& t3, const Vector3f& color1, const Vector3f& color2):
    TriangleTexture(t1, t2, t3), color1(color1), color2(color2)
{
}

Vector3f Checkerboard::getColor(const Vector3f& barycentric) const
{
    Vector2f uv = getUV(barycentric);
    int col = (int)uv.x() % 2;
    int row = (int)uv.y() % 2;
    if (row^col) {
        return color1;
    }
    return color2;
}

Vector2f Checkerboard::getUV(const Vector3f& barycentric) const
{
    Vector2f t = barycentric.x()*t1 + barycentric.y()*t2 + barycentric.z()*t3;
    return t;
}