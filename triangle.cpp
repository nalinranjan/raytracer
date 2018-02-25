// #include <iostream>
// #include <cmath>
#include "triangle.h"

Triangle::Triangle(const Vector3f& v1, const Vector3f& v2, const Vector3f& v3, const IlluminationModel& model, const std::string& name):
    vertices({v1, v2, v3}),
    Object(model, name)
{
}

void Triangle::transform(const Matrix4f& view)
{
    for (int i = 0; i < 3; ++i)
    {
        // std::cout << vertices[i] << std::endl;
        Vector4f h_vertex;
        h_vertex << vertices[i], 1.0;
        h_vertex = view * h_vertex;
        vertices[i] = h_vertex.head(3);
        // std::cout << vertices[i] << std::endl;
    }
}

float Triangle::intersect(const Ray& ray) const
{
    Vector3f e1 = vertices[1] - vertices[0];
    Vector3f e2 = vertices[2] - vertices[0];
    Vector3f P = ray.direction.cross(e2);

    float P_dot_e1 = P.dot(e1);
    if (P_dot_e1 == 0)
    {
        return -1;
    }

    Vector3f T = ray.origin - vertices[0];
    Vector3f Q = T.cross(e1);

    float t = Q.dot(e2) / P_dot_e1;

    if (t < 0)
    {
        return -1;
    }

    float u = P.dot(T) / P_dot_e1; 
    float v = Q.dot(ray.direction) / P_dot_e1;

    if ((u < 0) || (v < 0) || (u + v > 1))
    {
        return -1;
    }

    return t;
}

Vector3f Triangle::getNormal(const Vector3f&) const
{
    Vector3f normal = (vertices[1]-vertices[0]).cross(vertices[2]-vertices[0]);
    normal.normalize();
    return normal;
}

Vector3f Triangle::getPos() const
{
    return vertices[0];
}