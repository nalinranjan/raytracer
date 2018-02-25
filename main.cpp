#include <iostream>
// #include <memory>
#include <chrono>
#include <Eigen/Dense>
#include "object.h"
#include "sphere.h"
#include "triangle.h"
#include "cylinder.h"
#include "world.h"
#include "camera.h"
#include "light.h"
#include "illumination.h"
#include "phong.h"
#include "params.h"

using namespace Eigen;

int main(int argc, char const *argv[])
{
    auto start = std::chrono::high_resolution_clock::now();
    World world;
    
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

    IlluminationModel * ref_sphere = new Phong(params::ref_sphere::ka, params::ref_sphere::kd, params::ref_sphere::ks, params::ref_sphere::ke);
    Object * reflective = new Sphere(params::ref_sphere::center, params::ref_sphere::radius, *ref_sphere, "reflective");

    IlluminationModel * trans_sphere = new Phong(params::trans_sphere::ka, params::trans_sphere::kd, params::trans_sphere::ks, params::trans_sphere::ke);
    Object * transmissive = new Sphere(params::trans_sphere::center, params::trans_sphere::radius, *trans_sphere, "transmissive");

    IlluminationModel * floor = new Phong(params::floor_color::ka, params::floor_color::kd, params::floor_color::ks, params::floor_color::ke);
    Object * floor1 = new Triangle(params::floor1::v1, params::floor1::v2, params::floor1::v3, *floor, "floor1");
    Object * floor2 = new Triangle(params::floor2::v1, params::floor2::v2, params::floor2::v3, *floor, "floor2");

    // Object * cylinder = new Cylinder(params::cylinder::color, params::cylinder::center1, params::cylinder::center2, params::cylinder::radius);

    Light * source1 = new Light(params::light1::color, params::light1::position, params::light1::ambient);

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

    // delete reflective;
    // delete transmissive;
    // delete floor1;
    // delete floor2;
    // delete cylinder;

    // delete source1;

    return 0;
}