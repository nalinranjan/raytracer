#ifndef TONE_ADAPTIVE_LOG_H
#define TONE_ADAPTIVE_LOG_H

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
    void render_adaptive_log(std::vector<std::future<Vector3f>>&);
}


#endif