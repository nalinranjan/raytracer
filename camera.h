#ifndef CAMERA_H
#define CAMERA_H

#include <limits>
#include <array>
#include <vector>
#include <thread>
#include <Eigen/Dense>
#include <pngwriter.h>
#include "params.h"
#include "world.h"
#include "object.h"
#include "ray.h"
#include "intersect.h"
#include "ctpl_stl.h"

using namespace Eigen;

class Camera
{
public:
    Camera();
    Camera(const Vector3f&, const Vector3f&, const Vector3f&);
    void setEyepoint(float, float, float);
    void setLookat(float, float, float);
    void setUp(float, float, float);
    void calculateTransform();
    void printTransform();
    void render(const World&);
    void transformObjects(const std::vector<Object *>& objects) const;
    void transformLights(const std::vector<Light *>& lights) const;
    Vector3f illuminatePixel(int, int, int, float, float, const World&, const std::vector<Light *>&);
    Vector3f traceRay(const Ray&, int, const World&, const std::vector<Light *>&, float);
    float inShadow(const Ray&, const World&) const;
    static float getRandom();
    static float vignette(const Vector3f&);

private:
    Vector3f eyepoint, lookat, up;
    Matrix4f viewTransform;
};

#endif