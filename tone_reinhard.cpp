#include <iostream>
#include "tone_reinhard.h"

void tone_rep::render_reinhard(std::vector<std::future<Vector3f>>& screenFutures)
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

    float a = 0.18;
    float key = L_avg;
    // int i = params::img_width / 2, j = params::img_height / 2;
    // float key = 0.27*screenBuffer[j-1][i-1].x() + 0.67*screenBuffer[j-1][i-1].y() + 0.06*screenBuffer[j-1][i-1].z();
    // float key = 13;
    a /= key;

    pngwriter png(params::img_width, params::img_height, params::png_background, "out.png");

    for(int i = 1; i <= params::img_width; i++)
    {
        for (int j = 1; j <= params::img_height; j++)
        {
            Vector3f color = a * screenBuffer[j-1][i-1];
            float r = color.x() / (1 + color.x());
            float g = color.y() / (1 + color.y());
            float b = color.z() / (1 + color.z());
            png.plot(i, j, r, g, b);
        }
    }

    png.close();
}