#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <rtc_wdt.h>
#include <esp_task_wdt.h>
#include <math.h>
#include <vector>
#include <array>
#include <thread>

// #include "bitluni/DACGraphics.h"
// #include "bitluni/Mesh.h"

#include "render.hpp"
#include "utils.hpp"

#include "composite.hpp"
#include "rasterize.hpp"
#include "primitives.hpp"
#include "assets.hpp"


extern "C" void app_main(void)
{
    dac::init_dac();

    const auto samples = 2048;
    const auto space = linspace(0.0, 10*M_PI, samples);
    
    float t = 0;
    float t2 = 0;
    float t3 = 0;

    while (true) {
        auto waves = std::make_unique<std::vector<uint8_t>>();
        waves->reserve(samples * 2);

        float frequency = 0.1 * sin(t);
        float frequency2 = 0.1 * cos(t2);
        t += 0.01;
        if (t > M_TWOPI) {
            t = 0;
        }
        t2 += 0.03;
        if (t2 > M_TWOPI) {
            t2 = 0;
        }
        t3 += 0.07;
        if (t3 > M_TWOPI) {
            t3 = 0;
        }
        
        float scale_modifier = 0.2*sin(t3);

        float scale = 0.6 + scale_modifier;

        for (const auto sin_input : space) {
            uint8_t x = (scale*sin(sin_input*(2.0f+frequency))*cos(sin_input*(1.4f+frequency2)) + 1.0f) * (float)(255 / 2);
            uint8_t y = (scale*cos(sin_input*(2.0f+frequency))*cos(sin_input*(1.4f+frequency2)) + 1.0f) * (float)(255 / 2);
            waves->push_back(x);
            waves->push_back(y);
            // std::printf("in: %f, x: %d, y: %d\n", sin_input, x, y);
            // vTaskDelay(1);
        }

        dac::update_buffer(std::move(waves));

        vTaskDelay(pdMS_TO_TICKS(16));

    }
    
}
