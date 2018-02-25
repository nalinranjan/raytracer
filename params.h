#ifndef PARAMS_H
#define PARAMS_H

#include <Eigen/Dense>
// #include "color.h"
using namespace Eigen;

namespace params
{
    // Camera
    const Vector3f eyepoint(-1.8, 1.5, 5.3);
    const Vector3f lookat(-1.8, 1.5, 0.0);
    const Vector3f up(0.0, 1.0, 0.0);
    // const Vector3f eyepoint(7.5, 7.0, 1.8);
    // const Vector3f lookat(0.0, 0.0, 0.0);
    // const Vector3f up(0.0, 1.0, 0.0);

    // View plane
    const float view_width = 2.0;
    const float view_height = 1.125;
    const float f = 1.0;
    // const float view_width = 0.577;
    // const float view_height = 0.325;
    // const float f = 1.0;

    // Image
    const int img_width = 1280;
    const int img_height = 720;
    const float png_background = 0.7;
    const Vector3f img_background(0.2, 0.5, 0.8);

    // Reflective Sphere
    namespace ref_sphere
    {
        const Vector3f center(-0.8, 1.3, 1.5);
        const float radius = 0.65;
        const Vector3f ka(1.0, 0.1, 0.1);
        const Vector3f kd(0.8, 0.1, 0.1);
        const Vector3f ks(1.0, 1.0, 1.0);
        const float ke = 11.0;
    }

    // Transmissive Sphere
    namespace trans_sphere
    {
        const Vector3f center(-1.9, 1.9, 2.0);
        const float radius = 0.8;
        const Vector3f ka(0.0, 0.0, 0.8);
        const Vector3f kd(0.0, 0.0, 0.8);
        const Vector3f ks(1.0, 1.0, 1.0);
        const float ke = 9.0;
    }

    // Floor
    namespace floor_color
    {
        const Vector3f ka(0.93, 0.92, 0.23);
        const Vector3f kd(0.93, 0.92, 0.23);
        const Vector3f ks(0.4, 0.4, 0.4);
        const float ke = 1.0;
    }

    namespace floor1
    {
        const Vector3f v1(-4.2, 0.0, 9.0);
        const Vector3f v2(4.2, 0.0, 9.0);
        const Vector3f v3(-4.2, 0.0, -9.0);
    }
    namespace floor2
    {
        const Vector3f v1(4.2, 0.0, 9.0);
        const Vector3f v2(4.2, 0.0, -9.0);
        const Vector3f v3(-4.2, 0.0, -9.0);
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
        const Vector3f color(1.0, 1.0, 1.0);
        const Vector3f position(-1.3, 9.0, 10.0);
        const Vector3f ambient(0.2, 0.2, 0.2);
    }

    namespace light2
    {
        const Vector3f color(1.0, 1.0, 1.0);
        const Vector3f position(5.3, 3.0, 6.0);
        const Vector3f ambient(0.2, 0.2, 0.2);
    }
}

#endif