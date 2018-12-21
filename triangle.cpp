// #include <iostream>
// #include <cmath>
#include <algorithm>
#include "triangle.h"

Triangle::Triangle(const Vector3f& v1, const Vector3f& v2, const Vector3f& v3, const IlluminationModel& model, float kr, float kt, int max_depth, float ref_index, const std::string& name):
    Object(model, kr, kt, max_depth, ref_index, name),
    vertices({v1, v2, v3})
{
    // Cache values required to get Barycentric coordinates
    vec0 = v2 - v1;
    vec1 = v3 - v1;
    d00 = vec0.dot(vec0);
    d01 = vec0.dot(vec1);
    d11 = vec1.dot(vec1);
    invDenom = 1.0 / (d00 * d11 - d01 * d01);
}

void Triangle::makeAABB()
{
    aabb.set(std::min(std::min(vertices[0].x(), vertices[1].x()), vertices[2].x()),
             std::max(std::max(vertices[0].x(), vertices[1].x()), vertices[2].x()),
             std::min(std::min(vertices[0].y(), vertices[1].y()), vertices[2].y()),
             std::max(std::max(vertices[0].y(), vertices[1].y()), vertices[2].y()),
             std::min(std::min(vertices[0].z(), vertices[1].z()), vertices[2].z()),
             std::max(std::max(vertices[0].z(), vertices[1].z()), vertices[2].z()));
}

void Triangle::transform(const Matrix4f& view)
{
    for (int i = 0; i < 3; ++i)
    {
        Vector4f h_vertex;
        h_vertex << vertices[i], 1.0;
        h_vertex = view * h_vertex;
        vertices[i] = h_vertex.head(3);
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

Vector3f Triangle::getColor(const Vector3f& intersection_pt, const Light& light, const Vector3f& eyepoint) const
{
    return material->getColor(getIV(intersection_pt, light.position, eyepoint), light, getBarycentric(intersection_pt));
}

Vector3f Triangle::getAmbient(const Vector3f& intersection_pt, const Light& light) const
{
    return material->getAmbient(light, getBarycentric(intersection_pt));
}

Vector3f Triangle::getBarycentric(const Vector3f& point) const
{
    Vector3f vec2 = point - vertices[0];
    float d20 = vec2.dot(vec0);
    float d21 = vec2.dot(vec1);
    float v = (d11 * d20 - d01 * d21) * invDenom;
    float w = (d00 * d21 - d01 * d20) * invDenom;
    float u = 1.0f - v - w;
    return Vector3f(u, v, w);
}

Vector3f Triangle::getPos() const
{
    return vertices[0];
}