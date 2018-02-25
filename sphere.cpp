// #include <iostream>
#include <cmath>
#include "sphere.h"

Sphere::Sphere(const Vector3f& center, float radius, const IlluminationModel& model, const std::string& name):
    center(center),
    radius(radius),
    Object(model, name)
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

Vector3f Sphere::getNormal(const Vector3f& intersection_pt) const
{
    Vector3f normal = intersection_pt - center;
    normal.normalize();
    return normal;
}

// Vector3f Sphere::getColor(const IntersectVectors& iv, const Light& light) const
// {
//     return model->getColor(iv, light);
//     // Vector3f color(0.0, 1.0, 0.0);
//     // return color;
// }

// Vector3f Sphere::getAmbient(const Light& light)
// {
//     return model->getAmbient(light);
// }

// Vector3f Sphere::getPos() const
// {
//     return center;
// }