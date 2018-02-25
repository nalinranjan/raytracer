#include <cmath>
#include "phongblinn.h"

PhongBlinn::PhongBlinn(const Vector3f& ka, const Vector3f& kd, const Vector3f& ks, float ke):
    IlluminationModel(), ka(ka), kd(kd), ks(ks), ke(ke)
{
}

Vector3f PhongBlinn::getColor(const IntersectVectors& intersect, const Light& light) const
{
    Vector3f color = getAmbient(light);
    color += intersect.S.dot(intersect.N) * kd.cwiseProduct(light.color);
    color += std::pow(intersect.H.dot(intersect.N), ke) * ks.cwiseProduct(light.color);
    return color;
}

Vector3f PhongBlinn::getAmbient(const Light& light) const
{
    return light.ambient.cwiseProduct(ka);
}