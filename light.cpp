#include "light.h"

Light::Light(const Vector3f& color, const Vector3f& position, const Vector3f& ambient):
    color(color), position(position), ambient(ambient)
{
}

void Light::transform(const Matrix4f& view)
{
    Vector4f h_position;
    h_position << position, 1.0;
    h_position = view * h_position;
    position = h_position.head(3);
}