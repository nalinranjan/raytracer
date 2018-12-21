#include <iostream>
#include <algorithm>
#include "imgtexture.h"

ImgTexture::ImgTexture(const Vector2f& t1, const Vector2f& t2, const Vector2f& t3, const char *imgpath):
    TriangleTexture(t1, t2, t3), img(1, 1, 0.0, "dummy.png")
{
    float uMax = std::max(std::max(t1.x(), t2.x()), t3.x());
    float vMax = std::max(std::max(t1.y(), t2.y()), t3.y());
    
    img.readfromfile(imgpath);
    int width = img.getwidth();
    int height = img.getheight();

    uMult = width / uMax;
    vMult = height / vMax;
}

ImgTexture::~ImgTexture()
{
    img.close();
}

Vector3f ImgTexture::getColor(const Vector3f& barycentric) const
{
    Vector2f uv = getUV(barycentric);
    Vector3f color;
    for (int i = 1; i <= 3; i++)
    {
        color[i-1] = img.dread(uv.x() * uMult, uv.y() * vMult, i);
    }
    return color;
}

Vector2f ImgTexture::getUV(const Vector3f& barycentric) const
{
    Vector2f t = barycentric.x()*t1 + barycentric.y()*t2 + barycentric.z()*t3;
    return t;
}