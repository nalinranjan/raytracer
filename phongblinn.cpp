#include <cmath>
#include "phongblinn.h"

PhongBlinn::PhongBlinn(const Vector3f& ka, const Vector3f& kd, const Vector3f& ks, float ke, const TriangleTexture *texture):
    IlluminationModel(), texture(texture), ka(ka), kd(kd), ks(ks), ke(ke)
{
}

PhongBlinn::~PhongBlinn() 
{
    delete texture;
}

Vector3f PhongBlinn::getColor(const IntersectVectors& intersect, const Light& light, const Vector3f& texInfo) const
{
    Vector3f od = kd;
    if (texture)
    {
        od = texture->getColor(texInfo);
    }
    Vector3f color = intersect.S.dot(intersect.N) * od.cwiseProduct(light.color);
    color += std::pow(intersect.H.dot(intersect.N), ke) * ks.cwiseProduct(light.color);
    return color;
}

Vector3f PhongBlinn::getAmbient(const Light& light, const Vector3f& texInfo) const
{
    Vector3f oa = ka;
    if (texture)
    {
        oa = texture->getColor(texInfo);
    }
    return light.ambient.cwiseProduct(oa);
}
