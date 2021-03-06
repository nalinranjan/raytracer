#include <iostream>
#include <chrono>
#include <random>
#include <utility>
#include <cmath>
#include "camera.h"
#include "tone_ward.h"
#include "tone_reinhard.h"
#include "tone_adaptive_log.h"

Camera::Camera():
    eyepoint(params::eyepoint), lookat(params::lookat), up(params::up)
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
    auto lights = world.getLights();

    transformLights(lights);
    
    float pixel_width = params::view_width / params::img_width;
    float pixel_height = params::view_height / params::img_height;

    ctpl::thread_pool pool(params::threads);
    using namespace std::placeholders;
    std::vector<std::future<Vector3f>> screenBuffer(params::img_height * params::img_width); 

    auto start = std::chrono::high_resolution_clock::now();
    
    for(int i = 1; i <= params::img_width; i++)
    {
        for (int j = 1; j <= params::img_height; j++)
        {
            screenBuffer[(i-1)*params::img_height + (j-1)] = 
                pool.push([this, i, j, pixel_width, pixel_height, &world, &lights](int id) { 
                    return this->illuminatePixel(id, i, j, pixel_width, pixel_height, std::cref(world), std::cref(lights)); 
                });
        }
    }

    pool.stop(true);

    // tone_rep::render_ward(screenBuffer);
    // tone_rep::render_reinhard(screenBuffer);
    tone_rep::render_adaptive_log(screenBuffer);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Rendering: " << elapsed.count() << std::endl;
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

void Camera::transformLights(const std::vector<Light *>& lights) const
{
    auto start = std::chrono::high_resolution_clock::now();
    for (auto& light : lights)
    {
        light->transform(viewTransform);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    std::cout << "Light transformation: " << elapsed.count() << std::endl;
}

Vector3f Camera::illuminatePixel(int id, int i, int j, float pixel_width, float pixel_height, const World& world, const std::vector<Light *>& lights)
{
    Vector3f c = Vector3f::Zero();

    for (int k = 0; k < params::supersample; ++k)
    {
        float rand_x, rand_y;

        if (params::supersample > 1)
        {
            rand_x = getRandom();
            rand_y = getRandom();
        }
        else
        {
            rand_x = 0.5;
            rand_y = 0.5;
        }

        Vector3f direction(-1*params::view_width/2 + (i-rand_x)*pixel_width,
                           -1*params::view_height/2 + (j-rand_y)*pixel_height,
                           -params::f);
        direction.normalize();

        Ray ray(Vector3f::Zero(), direction);

        c += traceRay(ray, 0, world, lights, params::outside_ref_index);
    }

    c /= params::supersample;

    // Vector3f direction(-1*params::view_width/2 + (i-0.5)*pixel_width,
    //                    -1*params::view_height/2 + (j-0.5)*pixel_height,
    //                    -params::f);
    // direction.normalize();

    // c *= vignette(direction);

    return c;
}

Vector3f Camera::traceRay(const Ray& ray, int depth, const World& world, const std::vector<Light *>& lights, float ref_index)
{
    Vector3f color = Vector3f::Zero();
    auto objects = world.getHitObjects(ray);

    float min_w = std::numeric_limits<float>::max();
    const Object * hit_object = NULL;

    std::vector<Object *>::iterator i = objects.begin();

    while (i != objects.end())
    {
        if (*i == NULL)
        {
            if (!hit_object)
            {
                ++i;
                continue;
            }
            else
            {
                break;
            }
        }

        float w = (*i)->intersect(ray);
        if (w > 0.01 && w < min_w)
        {
            hit_object = *i;
            min_w = w;
        }
        ++i;
    }

    if (hit_object)
    {
        Vector3f intersection_pt = ray.origin + min_w*ray.direction;
        for (auto& light : lights)
        {
            Vector3f light_direction = light->position - intersection_pt;
            light_direction.normalize();

            float shadow_intensity = inShadow(Ray(intersection_pt, light_direction), world);
            color += hit_object->getAmbient(intersection_pt, *light);
            
            color += shadow_intensity * hit_object->getColor(intersection_pt, *light, eyepoint);

            if (depth < hit_object->getMaxDepth())
            {
                if (hit_object->getkr() > 0)
                {
                    Ray reflected_ray(intersection_pt, Object::reflect(ray.direction, hit_object->getNormal(intersection_pt)));
                    color += hit_object->getkr() * traceRay(reflected_ray, depth+1, world, lights, ref_index);
                }

                if (hit_object->getkt() > 0)
                {
                    float obj_ref_index = hit_object->getRefIndex();
                    float ref_index2 = (obj_ref_index  == ref_index)? params::outside_ref_index : obj_ref_index;
                    auto dir_tir = Object::transmit(ray.direction, hit_object->getNormal(intersection_pt), ref_index, ref_index2);
                    Ray transmitted_ray(intersection_pt, dir_tir.first);
                    color += hit_object->getkt() * traceRay(transmitted_ray, depth+1, world, lights, (dir_tir.second)? ref_index : ref_index2);
                }
            }
        }
    }
    else
    {
        for (auto& light : lights)
        {
            color += (light->color).cwiseProduct(params::img_background);
        }
    }

    return color;
}

float Camera::inShadow(const Ray& shadow_ray, const World& world) const
{
    auto objects = world.getHitObjects(shadow_ray);
    for (auto& obj : objects)
    {
        if (obj == NULL)
        {
            continue;
        }
        if (obj->intersect(shadow_ray) > 0.04)
        {
            return obj->getkt();
        }
    }
    return 1.0;
}

float Camera::getRandom()
{
    static std::default_random_engine e;
    static std::uniform_real_distribution<> rand(0, 1);
    return rand(e);
}

float Camera::vignette(const Vector3f& direction)
{
    static Vector3f toCenter(0.0, 0.0, -1.0);
    static float multiplier = M_PI / (4 * params::f_stop * params::f_stop);

    return multiplier * std::pow(direction.dot(toCenter), 4.0);
}
