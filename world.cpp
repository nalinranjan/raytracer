#include <iostream>
#include <fstream>
#include "world.h"
#include "triangle.h"
#include "phongblinn.h"

#include "tinyply.h"

using namespace tinyply;

World::World() 
{
}

World::~World()
{
    for (Object* obj : objects)
        delete obj;
    for (Light* light : lights)
        delete light;
    delete kdRoot;
    // delete defaultIllumination;
}

void World::addObject(Object * obj)
{
    objects.push_back(obj);
}

void World::addLight(Light * light)
{
    lights.push_back(light);
}

void World::addModel()
{
    try
    {
        std::ifstream ss(params::ply_filename, std::ios::binary);

        if (ss.fail()) 
        {
            throw std::runtime_error("failed to open " + params::ply_filename);
        }

        PlyFile file;

        file.parse_header(ss);

        std::shared_ptr<PlyData> vertices, faces;

        try { vertices = file.request_properties_from_element("vertex", { "x", "y", "z" }); }
        catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }
        
        try { faces = file.request_properties_from_element("face", { "vertex_indices" }); }
        catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

        file.read(ss);
        ss.close();

        const size_t numVerticesBytes = vertices->buffer.size_bytes();
        std::vector<Vector3f> verts(vertices->count);
        std::memcpy(verts.data(), vertices->buffer.get(), numVerticesBytes);

        const size_t numFacesBytes = faces->buffer.size_bytes();
        std::vector<Vector3i> indices(faces->count);
        std::memcpy(indices.data(), faces->buffer.get(), numFacesBytes);

        defaultIllumination = new PhongBlinn(params::model::ka, params::model::kd, params::model::ks, params::model::ke, NULL);

        for (auto triangleInd : indices)
        {
            addObject(new Triangle(verts.at(triangleInd.x()), verts.at(triangleInd.y()), verts.at(triangleInd.z()), *defaultIllumination, params::model::kr, params::model::kt, params::model::max_depth, params::model::ref_index));
        }
    }
    catch (const std::exception & e)
    {
        std::cerr << "Caught tinyply exception: " << e.what() << std::endl;
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

void World::makeAABB()
{
    for (Object* obj : objects)
    {
        obj->makeAABB();
        aabb.expand(obj->getAABB());
    }

    aabb.print();
}

void World::buildKdTree()
{
    kdRoot = new KdNode(objects, aabb);
}

std::vector<Object *> World::getHitObjects(const Ray& ray) const
{
    return kdRoot->getHitObjects(ray);
}

void World::print() const
{
    for (Object* obj : objects)
    {
        obj->print();
    }
}

void World::printKd() const
{
    kdRoot->print();
}

void World::sort()
{
    std::sort(objects.begin(), objects.end(), Object::cmpX);
}
