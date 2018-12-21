#include <iostream>
#include "tone_adaptive_log.h"

void tone_rep::render_adaptive_log(std::vector<std::future<Vector3f>>& screenFutures)
{
    float log_luminance = 0.0, L_wmax = 0, delta = 0.0001;
    std::vector<std::vector<Vector3f>> screenBuffer(params::img_height, std::vector<Vector3f>(params::img_width));
    std::vector<std::vector<float>> screenLuminances(params::img_height, std::vector<float>(params::img_width));

    for(int i = 1; i <= params::img_width; i++)
    {
        for (int j = 1; j <= params::img_height; j++)
        {
            screenBuffer[j-1][i-1] = screenFutures[(i-1)*params::img_height + (j-1)].get();

            float L = 0.27*screenBuffer[j-1][i-1].x() + 0.67*screenBuffer[j-1][i-1].y() + 0.06*screenBuffer[j-1][i-1].z();
            screenLuminances[j-1][i-1] = L;

            if (L > L_wmax)
            {
                L_wmax = L;
            }

            log_luminance += std::log(delta + ((L > 0)? L : 0.0)); 
        }
    }

    float L_wa = std::exp(log_luminance / (params::img_width * params::img_height));
    float invL_wa = 1.0 / L_wa;
    L_wmax *= invL_wa;
    float invLogL_wmax = 1 / std::log10(L_wmax + 1);
    float bias_exp = std::log(params::bias) / std::log(0.5);

    std::cout << "Total log luminance = " << log_luminance << " L_avg = " << L_wa << std::endl;

    pngwriter png(params::img_width, params::img_height, params::png_background, "out.png");

    for(int i = 1; i <= params::img_width; i++)
    {
        for (int j = 1; j <= params::img_height; j++)
        {
            float L_w = screenLuminances[j-1][i-1] * invL_wa;
            float L_d = invLogL_wmax * std::log(L_w + 1) / std::log(2 + std::pow(L_w / L_wmax, bias_exp) * 8);

            Vector3f color = L_d / params::light1::color.x() * screenBuffer[j-1][i-1];
            png.plot(i, j, color.x(),color.y(), color.z());
        }
    }

    png.close();
}