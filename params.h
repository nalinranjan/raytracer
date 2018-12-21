#ifndef PARAMS_H
#define PARAMS_H

#include <Eigen/Dense>
using namespace Eigen;

namespace params
{

    // Camera
    const Vector3f eyepoint(-1.8, 2.0, 5.5);
    const Vector3f lookat(-1.8, 1.5, 0.0);
    const Vector3f up(0.0, 1.0, 0.0);

    // const Vector3f eyepoint(0.0, 0.15, 2.0); // buddha
    // const Vector3f lookat(0.0, 0.15, 0.0);
    // const Vector3f up(0.0, 1.0, 0.0);

    // const Vector3f eyepoint(-0.01, 0.12, 2.0); // dragon
    // const Vector3f lookat(-0.01, 0.12, 0.0);
    // const Vector3f up(0.0, 1.0, 0.0);
    
    // const Vector3f eyepoint(-0.02, 0.1, 2.0); //bunny
    // const Vector3f lookat(-0.02, 0.1, 0.0);
    // const Vector3f up(0.0, 1.0, 0.0);

    // View plane
    const float view_width = 2.0;
    const float view_height = 1.125;
    const float f = 1.0;

    // const float view_width = 0.2; // bunny, dragon
    // const float view_height = 0.15;
    // const float f = 1.2;
    
    // const float view_width = 0.1; // buddha
    // const float view_height = 0.15;
    // const float f = 1.2;
    
    // Image
    const int img_width = 1280;
    const int img_height = 720;
    const float png_background = 0.7;
    const Vector3f img_background(0.2, 0.5, 0.8);

    // Reflective Sphere
    namespace ref_sphere
    {
        const Vector3f center(-0.8, 1.3, 0.9);
        const float radius = 0.65;
        const Vector3f ka(0.2, 0.2, 0.2);
        const Vector3f kd(0.4, 0.4, 0.4); // Whitted
        const Vector3f ks(0.05, 0.05, 0.05);
        // const Vector3f kd(0.45, 0.45, 0.45); // Importance sampling
        // const Vector3f ks(0.08, 0.08, 0.08);
        const float ke = 50.0;
        const float kr = 0.8;
        const float kt = 0.0;
        const int max_depth = 4;
        const float ref_index = 1.0;
    }

    // Transmissive Sphere
    namespace trans_sphere
    {
        const Vector3f center(-2.0, 1.53, 2.0);
        const float radius = 0.7;
        const Vector3f ka(0.3, 0.3, 0.3);
        const Vector3f kd(0.5, 0.6, 0.7);
        const Vector3f ks(0.05, 0.05, 0.05);
        const float ke = 100.0;
        const float kr = 0.0;
        const float kt = 0.6;
        const int max_depth = 6;
        const float ref_index = 0.95;
    }

    // Floor
    namespace floor_color
    {
        const Vector3f ka(0.93, 0.92, 0.23);
        const Vector3f kd(0.93, 0.92, 0.23);
        const Vector3f ks(0.35, 0.35, 0.35);
        const float ke = 1.0;
        const float kr = 0.0;
        const float kt = 0.0;
        const int max_depth = 0;
        const float ref_index = 1.0;
    }

    const Vector3f floor_color1(0.93, 0.92, 0.23);
    const Vector3f floor_color2(0.9, 0.1, 0.1);

    namespace floor1
    {
        const Vector3f v1(-4.2, 0.0, 9.0);
        const Vector3f v2(4.2, 0.0, 9.0);
        const Vector3f v3(-4.2, 0.0, -9.0);

        const Vector2f t1(0.0, 0.0);
        const Vector2f t2(15.0, 0.0);
        const Vector2f t3(0.0, 30.0);
    }
    namespace floor2
    {
        const Vector3f v1(4.2, 0.0, 9.0);
        const Vector3f v2(4.2, 0.0, -9.0);
        const Vector3f v3(-4.2, 0.0, -9.0);
    
        const Vector2f t1(15.0, 0.0);
        const Vector2f t2(15.0, 30.0);
        const Vector2f t3(0.0, 30.0);
    }

    // Cylinder
    namespace cylinder
    {
        const Vector3f center1(-1.8, 0.9, 3.4);
        const Vector3f center2(-1.8, 1.8, 3.4);
        const float radius = 0.3;
        const Vector3f ka(1.0, 1.0, 1.0);
        const Vector3f kd(0.0, 0.4, 0.0);
        const Vector3f ks(1.0, 1.0, 1.0);
        const float ke = 5.0;
    }

    namespace light1
    {
        // const Vector3f color(1.0, 1.0, 1.0);
        const Vector3f color(1000.0, 1000.0, 1000.0);
        const Vector3f position(-1.3, 9.0, 10.0);
        // const Vector3f ambient(0.4, 0.4, 0.4);
        const Vector3f ambient(400.0, 400.0, 400.0);
    }

    namespace light2
    {
        const Vector3f color(1.0, 1.0, 1.0);
        const Vector3f position(5.3, 3.0, 8.0);
        const Vector3f ambient(0.2, 0.2, 0.2);
    }

    // PLY model
    namespace model
    {
        const Vector3f ka(0.63, 0.51, 0.0);
        const Vector3f kd(0.63, 0.51, 0.0);
        const Vector3f ks(0.9, 0.8, 0.5);
        const float ke = 15.0;
        const float kr = 0.0;
        const float kt = 0.0;
        const int max_depth = 0;
        const float ref_index = 1.0;
    }

    const int supersample = 1;
    const int max_depth = 10;
    const int threads = 4;
    const int reflection_rays = 50;

    const float outside_ref_index = 1.0;

    // const std::string ply_filename = "bun_zipper.ply"; // depth 14
    const std::string ply_filename = "dragon_vrip.ply"; // depth 17
    // const std::string ply_filename = "happy_vrip.ply"; // depth 17?
    // const std::string ply_filename = "Armadillo.ply";

    const float Ld_max = 300.0;
    const float f_stop = 0.3;
    const float bias = 0.85;
}

#endif