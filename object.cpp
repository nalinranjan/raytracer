#include "object.h"

Object::Object(const Vector3f& c): 
    material(c)
{
}

void Object::setColor(const Vector3f& c)
{
    material = c;
}

Vector3f Object::getColor() const {
    return material;
}