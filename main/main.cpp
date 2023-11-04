#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <rtc_wdt.h>
#include <esp_task_wdt.h>
#include <math.h>
#include <vector>
#include <array>
#include <thread>

#include "render.hpp"
#include "utils.hpp"

#include "composite.hpp"
#include "rasterize.hpp"
#include "primitives.hpp"
#include "assets.hpp"


extern "C" void app_main(void)
{
    dac::init_dac();

    std::vector<Shape> scene;

    scene.push_back(primitives::square);
    // scene.back().rotate(45);
    scene.back().scale(0.5, 0.5);

    auto output_coords = rasterize(scene);

    dac::update_buffer(std::move(output_coords));

    while (true) {

        vTaskDelay(pdMS_TO_TICKS(16));

    }
    
}
