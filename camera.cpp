#include <iostream>
#include <chrono>
#include "camera.h"

Camera::Camera():
    eyepoint(params::eyepoint), lookat(params::lookat), up(params::up),
    screenBuffer(params::img_height, std::vector<Vector3f>(params::img_width))
{
    calculateTransform();
}

Camera::Camera(const Vector3f& eyepoint, const Vector3f& lookat, const Vector3f& up):
    eyepoint(eyepoint), lookat(lookat), up(up)
{
    calculateTransform();
}

void Camera::setEyepoint(float x, float y, float z)
{
    eyepoint << x, y, z;
}

void Camera::setLookat(float x, float y, float z)
{
    lookat << x, y, z;
}

void Camera::setUp(float x, float y, float z)
{
    up << x, y, z;
}

void Camera::calculateTransform()
{
    up.normalize();

    Vector3f n = (eyepoint - lookat);
    n.normalize();

    Vector3f u = up.cross(n);
    u.normalize();

    Vector3f v = n.cross(u);

    viewTransform << u.x(), u.y(), u.z(), -eyepoint.dot(u),
                     v.x(), v.y(), v.z(), -eyepoint.dot(v),
                     n.x(), n.y(), n.z(), -eyepoint.dot(n),
                       0.0,   0.0,   0.0,              1.0;
}

void Camera::printTransform()
{
    std::cout << viewTransform << std::endl;
}

void Camera::render(const World& world)
{
    auto objects = world.getObjects();

    transformObjects(objects);
    
    float pixel_width = params::view_width / params::img_width;
    float pixel_height = params::view_height / params::img_height;

    for(int i = 1; i <= params::img_width; i++)
    {
        for (int j = 1; j <= params::img_height; j++)
        {
            illuminatePixel(i, j, pixel_width, pixel_height, objects);
        }
    }

    pngwriter png(params::img_width, params::img_height, params::png_background, "out.png");

    for(int i = 1; i <= params::img_width; i++)
    {
        for (int j = 1; j <= params::img_height; j++)
        {
            png.plot(i, j, screenBuffer[j-1][i-1].x(),screenBuffer[j-1][i-1].y(), screenBuffer[j-1][i-1].z());
        }
    }

    png.close();
}

void Camera::transformObjects(const std::vector<Object *>& objects) const
{
    auto start = std::chrono::high_resolution_clock::now();
    for (auto& obj : objects)
    {
        obj->transform(viewTransform);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    std::cout << "Object transformation: " << elapsed.count() << std::endl;
}

void Camera::illuminatePixel(int i, int j, float pixel_width, float pixel_height, const std::vector<Object *>& objects)
{
    Vector3f direction(-1*params::view_width/2 + (i-0.5)*pixel_width,
                       -1*params::view_height/2 + (j-0.5)*pixel_height,
                       -params::f);
    direction.normalize();

    Ray ray(Vector3f(0.0, 0.0, 0.0), direction);

    Vector3f c = params::img_background;
    float min_w = std::numeric_limits<float>::max();
    Object * hit_object = NULL;

    for (auto& obj : objects)
    {
        float w = obj->intersect(ray);
        if (w > 0 && w < min_w)
        {
            hit_object = obj;
            min_w = w;
        }
    }

    if (hit_object)
    {
        c = hit_object->getColor();
    }

    screenBuffer.at(j-1).at(i-1) = c;
}