#include "object.h"

Object::Object(const IlluminationModel& model, const std::string& name): 
    material(&model), name(name)
{
}

Object::~Object()
{
    delete material;
}

Vector3f Object::getColor(const IntersectVectors& iv, const Light& light) const
{
    return material->getColor(iv, light);
    // Vector3f color(0.0, 1.0, 0.0);
    // return color;
}

Vector3f Object::getAmbient(const Light& light) const
{
    return material->getAmbient(light);
}

std::string Object::getName() const
{
    return name;
}

// void Object::setColor(const Vector3f& c)
// {
//     material = c;
// }

// Vector3f Object::getColor() const {
//     return material;
// }