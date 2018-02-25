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
    auto lights = world.getLights();

    transformObjects(objects);
    
    float pixel_width = params::view_width / params::img_width;
    float pixel_height = params::view_height / params::img_height;

    for(int i = 1; i <= params::img_width; i++)
    {
        for (int j = 1; j <= params::img_height; j++)
        {
            illuminatePixel(i, j, pixel_width, pixel_height, objects, lights);
        }
    }

    // correctTone();

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

void Camera::illuminatePixel(int i, int j, float pixel_width, float pixel_height, const std::vector<Object *>& objects, const std::vector<Light *>& lights)
{
    Vector3f direction(-1*params::view_width/2 + (i-0.5)*pixel_width,
                       -1*params::view_height/2 + (j-0.5)*pixel_height,
                       -params::f);
    direction.normalize();

    Ray ray(Vector3f::Zero(), direction);

    Vector3f c = Vector3f::Zero();
    float min_w = std::numeric_limits<float>::max();
    const Object * hit_object = NULL;

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
        Vector3f intersection_pt = ray.origin + min_w*ray.direction;
        for (auto& light : lights)
        {
            Vector3f light_direction = light->position - intersection_pt;
            if (inShadow(Ray(intersection_pt, light_direction), objects))
            {
                std::cout << hit_object->getName() << " in shadow at " << i << ", " << j << std::endl;
                c += hit_object->getAmbient(*light);
            }
            else
            {
                Vector3f normal = hit_object->getNormal(intersection_pt);
                c += hit_object->getColor(getIV(intersection_pt, normal, light->position), *light);
            }
        }
    }
    else
    {
        c = params::img_background;
    }

    screenBuffer.at(j-1).at(i-1) = c;
}

bool Camera::inShadow(const Ray& shadow_ray, const std::vector<Object *>& objects) const
{
    for (auto& obj : objects)
    {
        if (obj->intersect(shadow_ray) > 0.1)
        {
            std::cout << obj->getName() << " intersected by (" << shadow_ray.origin.x() 
                      << ", " << shadow_ray.origin.y() << ", " << shadow_ray.origin.z()
                      << ")->(" << shadow_ray.direction.x() << ", " << shadow_ray.direction.y()
                      << ", " << shadow_ray.direction.z() << ")\t"; 
            return true;
        }
    }
    return false;
}

IntersectVectors Camera::getIV(const Vector3f& point, const Vector3f& normal, const Vector3f& light) const
{
    // s,v,n,h,r
    Vector3f S = light - point;
    S.normalize();

    Vector3f V = eyepoint - point;
    V.normalize();

    Vector3f N = normal;

    Vector3f H = Vector3f::Zero();

    Vector3f R = reflect(-S, N);
    R.normalize();

    return IntersectVectors(S, V, N, H, R);
}

Vector3f Camera::reflect(const Vector3f& v, const Vector3f& n) const
{
    Vector3f reflected = v - 2*v.dot(n)*n;
    return reflected;
}

void Camera::correctTone()
{
    float r_max = screenBuffer.at(0).at(0).x();
    float g_max = screenBuffer.at(0).at(0).y();
    float b_max = screenBuffer.at(0).at(0).z();

    for (const auto& row : screenBuffer)
    {
        for (const auto& pixel : row)
        {
            if (pixel.x() > r_max)
            {
                r_max = pixel.x();
            }
            if (pixel.y() > g_max)
            {
                g_max = pixel.y();
            }
            if (pixel.z() > b_max)
            {
                b_max = pixel.z();
            }
        }
    }

    for (auto& row : screenBuffer)
    {
        for (auto& pixel : row)
        {
            pixel[0] /= r_max;
            pixel[1] /= g_max;
            pixel[2] /= b_max;
        }
    }    
}