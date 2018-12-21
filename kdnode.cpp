#include <iostream>
#include "kdnode.h"

KdNode::~KdNode()
{
    delete top;
    delete bottom;
}

KdNode::KdNode(std::vector<Object *>& objects, const AABB& aabb, int depth)
{
    plane_axis = depth % 3;
    this->aabb = aabb;
    if (objects.size() < 3 || depth >= params::max_depth)
    {
        top = NULL;
        bottom = NULL;
        this->objects = objects;
        plane_value = 0;
        return;
    }

    switch (plane_axis)
    {
        case 0: std::nth_element(objects.begin(), objects.begin() + objects.size()/2, objects.end(), Object::cmpX);
                break;
        case 1: std::nth_element(objects.begin(), objects.begin() + objects.size()/2, objects.end(), Object::cmpY);
                break;
        case 2: std::nth_element(objects.begin(), objects.begin() + objects.size()/2, objects.end(), Object::cmpZ);
                break;
    }

    plane_value = (*(objects.begin() + objects.size()/2))->getAABB().min[plane_axis];

    std::vector<Object *> topObjects(objects.begin(), objects.begin() + objects.size()/2);
    std::vector<Object *> bottomObjects(objects.begin() + objects.size()/2, objects.end());

    for (Object *obj : topObjects)
    {
        if (obj->getAABB().max[plane_axis] > plane_value)
        {
            bottomObjects.emplace_back(obj);
        }
    }

    AABB topAABB = AABB();
    topAABB.expand(aabb);
    topAABB.max[plane_axis] = plane_value;

    AABB bottomAABB = AABB();
    bottomAABB.expand(aabb);
    bottomAABB.min[plane_axis] = plane_value;

    top = new KdNode(topObjects, topAABB, depth+1);
    bottom = new KdNode(bottomObjects, bottomAABB, depth+1);
}

std::vector<Object *> KdNode::getHitObjects(const Ray& ray) const
{
    if (objects.size() > 0)
    {
        return objects;
    }

    std::pair<float, float> t;

    if (!intersects(ray, t))
    {
        return {};
    }

    t.first = std::max(t.first, 0.0f);

    float c1 = ray.origin[plane_axis] + t.first * ray.direction[plane_axis];
    float c2 = ray.origin[plane_axis] + t.second * ray.direction[plane_axis];

    if (c1 <= plane_value)
    {
        if (c2 <= plane_value)
        {
            return top->getHitObjects(ray);
        }
        auto hitObjects = top->getHitObjects(ray);
        hitObjects.emplace_back((Object *)NULL);
        auto bottomObjects = bottom->getHitObjects(ray);
        hitObjects.insert(hitObjects.end(), bottomObjects.begin(), bottomObjects.end());
        return hitObjects;
    }
    else if (c2 >= plane_value)
    {
        return bottom->getHitObjects(ray);
    }
    else
    {
        auto hitObjects = bottom->getHitObjects(ray);
        hitObjects.emplace_back((Object *)NULL);
        auto topObjects = top->getHitObjects(ray);
        hitObjects.insert(hitObjects.end(), topObjects.begin(), topObjects.end());
        return hitObjects;   
    }
}

bool KdNode::intersects(const Ray& ray, std::pair<float, float>& t) const
{
    float t_min, t_max, temp_min, temp_max;

    float div_x = 1 / ((ray.direction.x() == 0)? 0.00001 : ray.direction.x());
    if (div_x >= 0)
    {
        t_min = (aabb.min[0] - ray.origin.x()) * div_x;
        t_max = (aabb.max[0] - ray.origin.x()) * div_x;
    }
    else
    {
        t_min = (aabb.max[0] - ray.origin.x()) * div_x;
        t_max = (aabb.min[0] - ray.origin.x()) * div_x;
    }

    float div_y = 1 / ((ray.direction.y() == 0)? 0.00001 : ray.direction.y());
    if (div_y >= 0)
    {
        temp_min = (aabb.min[1] - ray.origin.y()) * div_y;
        temp_max = (aabb.max[1] - ray.origin.y()) * div_y;
    }
    else
    {
        temp_min = (aabb.max[1] - ray.origin.y()) * div_y;
        temp_max = (aabb.min[1] - ray.origin.y()) * div_y;
    }

    if ((t_min > temp_max) || (t_max < temp_min))
    {
        return false;
    }

    t_min = std::max(t_min, temp_min);
    t_max = std::min(t_max, temp_max);

    float div_z = 1 / ((ray.direction.z() == 0)? 0.00001 : ray.direction.z());
    if (div_z >= 0)
    {
        temp_min = (aabb.min[2] - ray.origin.z()) * div_z;
        temp_max = (aabb.max[2] - ray.origin.z()) * div_z;
    }
    else
    {
        temp_min = (aabb.max[2] - ray.origin.z()) * div_z;
        temp_max = (aabb.min[2] - ray.origin.z()) * div_z;
    }

    if ((t_min > temp_max) || (t_max < temp_min))
    {
        return false;
    }

    t_min = std::max(t_min, temp_min);
    t_max = std::min(t_max, temp_max);

    t.first = t_min;
    t.second = t_max;

    return true;
}

void KdNode::print() const
{
    std::cout << "Axis: " << plane_axis << " Value: " << plane_value << " Objects: " << objects.size() << " ";// << std::endl;

    aabb.print();

    if (top)
    {
        top->print();
    }
    if (bottom)
    {
        bottom->print();
    }
}