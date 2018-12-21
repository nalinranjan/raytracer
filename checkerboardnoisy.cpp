#include "checkerboardnoisy.h"

CheckerboardNoisy::CheckerboardNoisy(const Vector2f& t1, const Vector2f& t2, const Vector2f& t3, const Vector3f& color1, const Vector3f& color2):
    TriangleTexture(t1, t2, t3), color1(color1), color2(color2)
{
}

Vector3f CheckerboardNoisy::getColor(const Vector3f& barycentric) const
{
    Vector2f uv = getUV(barycentric);
    int col = (int)uv.x();
    int row = (int)uv.y();

    float n = (float) pn.noise(col*10, row*10, 5.8) * 1.3 - 1;

    if ((row % 2) ^ (col % 2)) {
        return color1 + Vector3f(n, n, 0.0);
    }
    return color2 + Vector3f(n, 0.0, 0.0);
}

Vector2f CheckerboardNoisy::getUV(const Vector3f& barycentric) const
{
    Vector2f t = barycentric.x()*t1 + barycentric.y()*t2 + barycentric.z()*t3;
    return t;
}