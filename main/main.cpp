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

#include "dacGraphics.hpp"
#include "utils.hpp"

#include "composite.hpp"
#include "rasterize.hpp"
#include "primitives.hpp"
#include "assets.hpp"


extern "C" void app_main(void)
{
    const auto samples = 2048;
    const auto space = linspace(0.0, 10*M_PI, samples);
    
    auto waves = std::make_unique<std::vector<uint8_t>>();
    waves->reserve(samples * 2);

    for (const auto sin_input : space) {
        uint8_t x = (sin(sin_input*2.0f)*cos(sin_input*1.4f) + 1.0f) * (float)(255 / 2);
        uint8_t y = (cos(sin_input*2.0f)*cos(sin_input*1.4f) + 1.0f) * (float)(255 / 2);
        waves->push_back(x);
        waves->push_back(y);
        // std::printf("in: %f, x: %d, y: %d\n", sin_input, x, y);
        // vTaskDelay(1);
    }

    dac::update_buffer(std::move(waves));

    while (true) {

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
