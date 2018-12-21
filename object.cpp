#include <iostream>
#include <cmath>
#include "object.h"

Object::Object(const IlluminationModel& model, float kr, float kt, int max_depth, float ref_index, const std::string& name): 
    material(&model), name(name), kr(kr), kt(kt), max_depth(max_depth), ref_index(ref_index)
{
}

Object::~Object() 
{
    delete material;
}

std::string Object::getName() const
{
    return name;
}

const AABB& Object::getAABB() const
{
    return aabb;
}

void Object::print() const
{
    std::cout << getName() << " ";
    aabb.print();
}

bool Object::cmpX(const Object *obj1, const Object *obj2)
{
    return obj1->aabb.cmp(obj2->aabb, 0);
}

bool Object::cmpY(const Object *obj1, const Object *obj2)
{
    return obj1->aabb.cmp(obj2->aabb, 1);
}

bool Object::cmpZ(const Object *obj1, const Object *obj2)
{
    return obj1->aabb.cmp(obj2->aabb, 2);
}

IntersectVectors Object::getIV(const Vector3f& intersection_pt, const Vector3f& light_pos, const Vector3f& eyepoint) const
{
    // s,v,n,h,r
    Vector3f S = light_pos - intersection_pt;
    S.normalize();

    Vector3f V = eyepoint - intersection_pt;
    V.normalize();

    Vector3f N = getNormal(intersection_pt);

    Vector3f H = V + S;
    H.normalize();

    Vector3f R = reflect(-S, N);
    R.normalize();

    return IntersectVectors(S, V, N, H, R);
}

Vector3f Object::reflect(const Vector3f& v, const Vector3f& n)
{
    Vector3f reflected = v - 2*v.dot(n)*n;
    return reflected;
}

std::pair<Vector3f, bool> Object::transmit(const Vector3f& d, const Vector3f& n, const float& u1, const float& u2)
{
    if (u1 == u2)
    {
        return std::make_pair(d, false);
    }

    Vector3f normal = (d.dot(n) > 0)? n : -n;
    float u1_div_u2 = u1 / u2, d_dot_n = d.dot(normal);

    float tir_check = u1_div_u2*u1_div_u2 * (1 - d_dot_n*d_dot_n);
    if (tir_check > 1)
    {
        return std::make_pair(reflect(d, normal), true);
    }

    Vector3f transmitted = (u1_div_u2 * (d - d_dot_n*normal)) + (std::sqrt(1 - tir_check) * normal);
    return std::make_pair(transmitted, false);
}

float Object::getkr() const
{
    return kr;
}

float Object::getkt() const
{
    return kt;
}

int Object::getMaxDepth() const
{
    return max_depth;
}

float Object::getRefIndex() const
{
    return ref_index;
}
