#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <Eigen/Dense>
#include "object.h"
#include "light.h"
using namespace Eigen;

class World
{
public:
    // World(Vector3f);
    World();
    ~World();
    void addObject(Object *);
    void addLight(Light *);
    std::vector<Object *> getObjects() const;
    std::vector<Light *> getLights() const;
    void printColors() const;
    // Vector3f getAmbientLight() const;

private:
    std::vector<Object *> objects;
    std::vector<Light *> lights;
    // Vector3f ambient;
};

#endif