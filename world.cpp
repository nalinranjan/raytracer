#include <iostream>
#include "world.h"

World::World(Vector3f ambient):
    ambient(ambient)
{
}

void World::addObject(Object * obj)
{
    objects.push_back(obj);
}

void World::addLight(Light * light)
{
    lights.push_back(light);
}

void World::printColors() const
{
    for (auto& obj : objects)
    {
        Vector3f c = obj->getColor();
        std::cout << c.x() << c.y() << c.z() << std::endl;
    }
}

std::vector<Object *> World::getObjects() const
{
    return objects;
}

std::vector<Light *> World::getLights() const
{
    return lights;
}

Vector3f World::getAmbientLight() const 
{
    return ambient;
}
