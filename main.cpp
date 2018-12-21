#include <iostream>
#include <chrono>
#include <Eigen/Dense>
#include "object.h"
#include "sphere.h"
#include "triangle.h"
#include "world.h"
#include "camera.h"
#include "light.h"
#include "triangletex.h"
#include "checkerboard.h"
#include "checkerboardnoisy.h"
#include "trytexture.h"
#include "imgtexture.h"
#include "illumination.h"
#include "phong.h"
#include "phongblinn.h"
#include "params.h"

using namespace Eigen;

int main(int argc, char const *argv[])
{
    // const char *tex_img = "road.png";

    auto start = std::chrono::high_resolution_clock::now();
    World world;

    // IlluminationModel * ref_sphere = new Phong(params::ref_sphere::ka, params::ref_sphere::kd, params::ref_sphere::ks, params::ref_sphere::ke);
    IlluminationModel * ref_sphere = new PhongBlinn(params::ref_sphere::ka, params::ref_sphere::kd, params::ref_sphere::ks, params::ref_sphere::ke, NULL);
    Object * reflective = new Sphere(params::ref_sphere::center, params::ref_sphere::radius, *ref_sphere, params::ref_sphere::kr, params::ref_sphere::kt, params::ref_sphere::max_depth, params::ref_sphere::ref_index, "reflective");

    // IlluminationModel * trans_sphere = new Phong(params::trans_sphere::ka, params::trans_sphere::kd, params::trans_sphere::ks, params::trans_sphere::ke);
    IlluminationModel * trans_sphere = new PhongBlinn(params::trans_sphere::ka, params::trans_sphere::kd, params::trans_sphere::ks, params::trans_sphere::ke, NULL);
    Object * transmissive = new Sphere(params::trans_sphere::center, params::trans_sphere::radius, *trans_sphere, params::trans_sphere::kr, params::trans_sphere::kt, params::trans_sphere::max_depth, params::trans_sphere::ref_index, "transmissive");

    TriangleTexture * floor_tex1 = new Checkerboard(params::floor1::t1, params::floor1::t2, params::floor1::t3, params::floor_color1, params::floor_color2);
    // TriangleTexture * floor_tex1 = new CheckerboardNoisy(params::floor1::t1, params::floor1::t2, params::floor1::t3, params::floor_color1, params::floor_color2);
    // TriangleTexture * floor_tex1 = new ImgTexture(params::floor1::t1, params::floor1::t2, params::floor1::t3, tex_img);
    // TriangleTexture * floor_tex1 = new TryTexture(params::floor1::t1, params::floor1::t2, params::floor1::t3);
    IlluminationModel * floor_mat1 = new PhongBlinn(params::floor_color::ka, params::floor_color::kd, params::floor_color::ks, params::floor_color::ke, floor_tex1);
    Object * floor1 = new Triangle(params::floor1::v1, params::floor1::v2, params::floor1::v3, *floor_mat1, params::floor_color::kr, params::floor_color::kt, params::floor_color::max_depth, params::floor_color::ref_index, "floor1");
    
    TriangleTexture * floor_tex2 = new Checkerboard(params::floor2::t1, params::floor2::t2, params::floor2::t3, params::floor_color1, params::floor_color2);
    // TriangleTexture * floor_tex2 = new CheckerboardNoisy(params::floor2::t1, params::floor2::t2, params::floor2::t3, params::floor_color1, params::floor_color2);
    // TriangleTexture * floor_tex2 = new ImgTexture(params::floor2::t1, params::floor2::t2, params::floor2::t3, tex_img);
    // TriangleTexture * floor_tex2 = new TryTexture(params::floor2::t1, params::floor2::t2, params::floor2::t3);
    IlluminationModel * floor_mat2 = new PhongBlinn(params::floor_color::ka, params::floor_color::kd, params::floor_color::ks, params::floor_color::ke, floor_tex2);
    Object * floor2 = new Triangle(params::floor2::v1, params::floor2::v2, params::floor2::v3, *floor_mat2, params::floor_color::kr, params::floor_color::kt, params::floor_color::max_depth, params::floor_color::ref_index, "floor2");

    Light * source1 = new Light(params::light1::color, params::light1::position, params::light1::ambient);
    // Light * source2 = new Light(params::light2::color, params::light2::position, params::light2::ambient);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "World, light creation: " << elapsed.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    // world.addModel();
    world.addObject(reflective);
    world.addObject(transmissive);
    world.addObject(floor1);
    world.addObject(floor2);

    world.addLight(source1);
    // world.addLight(source2);

    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Object addition to world: " << elapsed.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    Camera camera;
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Camera creation: " << elapsed.count() << std::endl;

    camera.transformObjects(world.getObjects());

    world.makeAABB();

    start = std::chrono::high_resolution_clock::now();
    world.buildKdTree();
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Kd build: " << elapsed.count() << std::endl;

    // world.printKd();

    camera.render(world);

    return 0;
}