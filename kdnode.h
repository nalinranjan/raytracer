#ifndef KDNODE_H
#define KDNODE_H

#include <vector>
#include <algorithm>
#include <utility>
#include "object.h"
#include "aabb.h"
#include "params.h"

class KdNode
{
public:
    KdNode(std::vector<Object *>&, const AABB&, int=0);
    ~KdNode();
    std::vector<Object *> getHitObjects(const Ray&) const;
    bool intersects(const Ray&, std::pair<float, float>&) const;
    void print() const;

    unsigned short plane_axis;
    float plane_value;
    KdNode *top, *bottom;
    std::vector<Object *> objects;
    AABB aabb;
};

#endif