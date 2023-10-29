#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <rtc_wdt.h>
#include <esp_task_wdt.h>
#include <driver/dac_cosine.h>
#include <math.h>
#include <vector>
#include <array>
#include <thread>

#include "bitluni/DACGraphics.h"
#include "bitluni/Mesh.h"

void blit(const std::vector<std::array<uint8_t, 4>>& lines) {
    // May want to replace this with the stanrdard library DAC calls at some point.
    // it's currently using the oudated driver API.  Maybe the new one isn't as slow.
    // (thus eliminating the need for the fastdac code)
    DACGraphics::begin(); 
    for (const auto &line: lines) {
        DACGraphics::line(line[0], line[1], line[2], line[3]);
    }
    DACGraphics::end();
}

extern "C" void app_main(void)
{
    DACGraphics::init();
    std::vector<std::array<uint8_t, 4>> square {
        {16,16,16,240},
        {16,240,240,240},
        {240,240,240,16},
        {240,16,16,16},
    };

    while (true) {
        for (int i = 0; i < 1e2; i++)
            blit(square);
        vTaskDelay(1);
    }
}
