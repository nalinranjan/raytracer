#include <cmath>
#include "phong.h"

Phong::Phong(const Vector3f& ka, const Vector3f& kd, const Vector3f& ks, float ke):
    IlluminationModel(), ka(ka), kd(kd), ks(ks), ke(ke)
{
}

Vector3f Phong::getColor(const IntersectVectors& intersect, const Light& light, const Vector3f& texInfo) const
{
    Vector3f color = getAmbient(light);
    color += intersect.S.dot(intersect.N) * kd.cwiseProduct(light.color);
    color += std::pow(intersect.R.dot(intersect.V), ke) * ks.cwiseProduct(light.color);
    return color;
}

Vector3f Phong::getAmbient(const Light& light, const Vector3f& texInfo) const
{
    return light.ambient.cwiseProduct(ka);
}