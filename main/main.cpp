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

// void blit(const std::vector<std::array<uint8_t, 4>>& lines) {
//     // May want to replace this with the stanrdard library DAC calls at some point.
//     // it's currently using the oudated driver API.  Maybe the new one isn't as slow.
//     // (thus eliminating the need for the fastdac code)
//     DACGraphics::begin(); 
//     for (const auto &line: lines) {
//         DACGraphics::line(line[0], line[1], line[2], line[3]);
//     }
//     DACGraphics::end();
// }

extern "C" void app_main(void)
{
    // DACGraphics::init();
    // std::vector<std::array<uint8_t, 4>> square {
    //     {16,16,16,240},
    //     {16,240,240,240},
    //     {240,240,240,16},
    //     {240,16,16,16},
    // };

    const auto samples = 2048;
    const auto space = linspace(0.0, 10*M_PI, samples);
    
    auto waves = std::make_unique<std::vector<uint8_t>>();
    waves->reserve(samples * 2);
    // for (int i = 0; i < samples; i++) {
        // float sin_input = i * M_TWOPI / (samples / 4);
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
        // for (int i = 0; i < 1e2; i++)
        //     blit(square);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
