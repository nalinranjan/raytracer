#include <iostream>
#include <limits>
#include "aabb.h"

AABB::AABB() 
{
    for (int i = 0; i < 3; ++i)
    {
        min[i] = std::numeric_limits<float>::max();
        max[i] = std::numeric_limits<float>::lowest();
    }
}

AABB::AABB(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax):
    min{xMin, yMin, zMin}, max{xMax, yMax, zMax}
{
}

void AABB::set(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
    min[0] = xMin;
    min[1] = yMin;
    min[2] = zMin;
    max[0] = xMax;
    max[1] = yMax;
    max[2] = zMax;
}

void AABB::expand(const AABB& other)
{
    for (int i = 0; i < 3; ++i)
    {
        min[i] = (other.min[i] < min[i])? other.min[i] : min[i];
        max[i] = (other.max[i] > max[i])? other.max[i] : max[i];
    }
}

bool AABB::cmp(const AABB& other, int axis) const
{
    return min[axis] < other.min[axis];
}

void AABB::print() const
{
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "(" << min[i] << ", " << max[i] << ") ";
    }
    std::cout << std::endl;
}