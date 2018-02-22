// #include <iostream>
#include <cmath>
#include "sphere.h"

Sphere::Sphere(const Vector3f& material, const Vector3f& center, float radius):
    Object(material),
    center(center),
    radius(radius)
{
}

void Sphere::transform(const Matrix4f& view)
{
    Vector4f h_center;
    h_center << center, 1.0;
    h_center = view * h_center;
    center = h_center.head(3);
}

float Sphere::intersect(const Ray& ray) const
{
    float B = 2 * (ray.direction.x()*(ray.origin.x() - center.x())
                 + ray.direction.y()*(ray.origin.y() - center.y())
                 + ray.direction.z()*(ray.origin.z() - center.z()));

    float C = (ray.origin.x() - center.x())*(ray.origin.x() - center.x())
              + (ray.origin.y() - center.y())*(ray.origin.y() - center.y())
              + (ray.origin.z() - center.z())*(ray.origin.z() - center.z())
              - radius*radius;

    float D = B*B - 4*C;

    if (D < 0)
    {
        return -1.0;
    }

    float w1 = (-B - std::sqrt(D))/2;
    if (w1 > 0) {
        return w1;
    }

    return (-B + std::sqrt(D))/2;
}

// Vector3f Sphere::getPos() const
// {
//     return center;
// }