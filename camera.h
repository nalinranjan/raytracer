#ifndef CAMERA_H
#define CAMERA_H

#include <limits>
#include <array>
#include <vector>
#include <Eigen/Dense>
#include <pngwriter.h>
#include "params.h"
#include "world.h"
#include "object.h"
// #include "color.h"
#include "ray.h"

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
    // void transformObjects(const World&) const;
    void transformObjects(const std::vector<Object *>& objects) const;
    // void illuminatePixel(int, int, float, float, const World&);
    void illuminatePixel(int, int, float, float, const std::vector<Object *>& objects);

private:
    Vector3f eyepoint, lookat, up;
    Matrix4f viewTransform;
    std::vector<std::vector<Vector3f>> screenBuffer;
};

#endif