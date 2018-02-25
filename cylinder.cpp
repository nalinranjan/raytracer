// #include <iostream>
#include <cmath>
#include "cylinder.h"

Cylinder::Cylinder(const Vector3f& center1, const Vector3f& center2, float radius, const IlluminationModel& model, const std::string& name):
    centers({center1, center2}),
    radius(radius),
    Object(model, name)
{
}

void Cylinder::transform(const Matrix4f& view)
{
    for (int i = 0; i < 2; ++i)
    {
        Vector4f h_center;
        h_center << centers[i], 1.0;
        h_center = view * h_center;
        centers[i] = h_center.head(3);
    }
}

float Cylinder::intersect(const Ray& ray) const
{
    // Cylinder [A, B, r]
    // Ray [O + Vt]

    Vector3f AO = ray.origin - centers[0];
    Vector3f AB = centers[1] - centers[0];

    Vector3f AOxAB = AO.cross(AB);
    Vector3f VxAB = ray.direction.cross(AB);
    float ab2 = AB.dot(AB);
    float a = VxAB.dot(VxAB);
    float b = 2 * VxAB.dot(AOxAB);
    float c = (AOxAB.dot(AOxAB)) - (radius*radius * ab2);

    float D = b*b - 4*a*c;
    if (D < 0)
    {
        return -1;
    }

    float t1 = (-b - std::sqrt(D))/(2*a);
    float t2 = (-b + std::sqrt(D))/(2*a);
    if (t2 < 0)
    {
        return -1;
    }

    if (t1 > 0)
    {
        Vector3f T = ray.origin + t1*ray.direction;
        if ((AB.dot(T - centers[0]) > 0) && (AB.dot(T - centers[1]) < 0))
        {
            return t1;
        }
    }

    Vector3f T = ray.origin + t2*ray.direction;
    if ((AB.dot(T - centers[0]) > 0) && (AB.dot(T - centers[1]) < 0))
    {
        return t2;
    }
    return -1;
}

Vector3f Cylinder::getPos() const
{
    return centers[0];
}