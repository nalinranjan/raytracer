#ifndef TONE_WARD_H
#define TONE_WARD_H

#include <future>
#include <thread>
#include <cmath>
#include <vector>
#include <pngwriter.h>
#include <Eigen/Dense>
#include "params.h"

using namespace Eigen;

namespace tone_rep
{
    void render_ward(std::vector<std::future<Vector3f>>&);
}


#endif