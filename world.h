#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <Eigen/Dense>
#include "object.h"
#include "light.h"
#include "aabb.h"
#include "illumination.h"
#include "kdnode.h"
#include "ray.h"
#include "params.h"
using namespace Eigen;

class World
{
public:
    World();
    ~World();
    void addObject(Object *);
    void addLight(Light *);
    void addModel();
    std::vector<Object *> getObjects() const;
    std::vector<Light *> getLights() const;
    std::vector<Object *> getHitObjects(const Ray&) const;
    void makeAABB();
    void buildKdTree();
    void print() const;
    void printKd() const;
    void sort();

private:
    std::vector<Object *> objects;
    std::vector<Light *> lights;
    AABB aabb;
    KdNode * kdRoot;
    IlluminationModel * defaultIllumination;
};

#endif