#include <iostream>
#include "tone_ward.h"

void tone_rep::render_ward(std::vector<std::future<Vector3f>>& screenFutures)
{
    float log_luminance = 0.0, delta = 0.00001;
    std::vector<std::vector<Vector3f>> screenBuffer(params::img_height, std::vector<Vector3f>(params::img_width));

    for(int i = 1; i <= params::img_width; i++)
    {
        for (int j = 1; j <= params::img_height; j++)
        {
            screenBuffer[j-1][i-1] = screenFutures[(i-1)*params::img_height + (j-1)].get();

            float L = 0.27*screenBuffer[j-1][i-1].x() + 0.67*screenBuffer[j-1][i-1].y() + 0.06*screenBuffer[j-1][i-1].z();

            log_luminance += std::log(delta + ((L > 0)? L : 0.0)); 
        }
    }

    float L_avg = std::exp(log_luminance / (params::img_width * params::img_height));

    std::cout << "Total log luminance = " << log_luminance << " L_avg = " << L_avg << std::endl;

    float sf = std::pow((1.219 + std::pow(params::Ld_max / 2.0, 0.4)) / (1.219 + std::pow(L_avg, 0.4)), 2.5);
    sf /= params::Ld_max;

    pngwriter png(params::img_width, params::img_height, params::png_background, "out.png");

    for(int i = 1; i <= params::img_width; i++)
    {
        for (int j = 1; j <= params::img_height; j++)
        {
            Vector3f color = sf * screenBuffer[j-1][i-1];
            png.plot(i, j, color.x(),color.y(), color.z());
        }
    }

    png.close();
}