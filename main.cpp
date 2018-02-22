#include <iostream>
#include <memory>
#include <chrono>
#include <Eigen/Dense>
#include <pngwriter.h>
#include "object.h"
#include "sphere.h"
#include "triangle.h"
#include "cylinder.h"
#include "color.h"
#include "world.h"
#include "camera.h"
#include "light.h"
#include "params.h"

using namespace Eigen;

int main(int argc, char const *argv[])
{
    auto start = std::chrono::high_resolution_clock::now();
    World world(params::ambient);
    
    // std::unique_ptr<Sphere> reflective = std::make_unique<Sphere>(
    //     params::ref_color, params::ref_center, params::ref_radius
    // );
    
    // std::unique_ptr<Sphere> transmissive = std::make_unique<Sphere>(
    //     params::trans_color, params::trans_center, params::trans_radius
    // );

    // std::unique_ptr<Triangle> floor1 = std::make_unique<Triangle>(
    //     params::floor_color, params::floor1::v1, params::floor1::v2, params::floor1::v3
    // );

    // std::unique_ptr<Triangle> floor2 = std::make_unique<Triangle>(
    //     params::floor_color, params::floor2::v1, params::floor2::v2, params::floor2::v3
    // );

    // std::unique_ptr<Cylinder> cylinder = std::make_unique<Cylinder>(
    //     params::cylinder::color, params::cylinder::center1, params::cylinder::center2, params::cylinder::radius
    // );

    Object * reflective = new Sphere(params::ref_color, params::ref_center, params::ref_radius);
    Object * transmissive = new Sphere(params::trans_color, params::trans_center, params::trans_radius);
    Object * floor1 = new Triangle(params::floor_color, params::floor1::v1, params::floor1::v2, params::floor1::v3);
    Object * floor2 = new Triangle(params::floor_color, params::floor2::v1, params::floor2::v2, params::floor2::v3);
    // Object * cylinder = new Cylinder(params::cylinder::color, params::cylinder::center1, params::cylinder::center2, params::cylinder::radius);

    Light * source1 = new Light(params::light1::color, params::light1::position);

    auto end = std::chrono::high_resolution_clock::now();

    // auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "World, object creation: " << elapsed.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    world.addObject(reflective);
    world.addObject(transmissive);
    world.addObject(floor1);
    world.addObject(floor2);
    // world.addObject(cylinder);

    world.addLight(source1);

    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Object addition to world: " << elapsed.count() << std::endl;

    // Camera camera(params::eyepoint, params::lookat, params::up);
    
    start = std::chrono::high_resolution_clock::now();
    Camera camera;
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Camera creation: " << elapsed.count() << std::endl;
    // camera.printTransform();
    
    start = std::chrono::high_resolution_clock::now();
    camera.render(world);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Rendering: " << elapsed.count() << std::endl;
    // std::cout << "inb4 ss" << std::endl;

    delete reflective;
    delete transmissive;
    delete floor1;
    delete floor2;
    // delete cylinder;

    return 0;
}