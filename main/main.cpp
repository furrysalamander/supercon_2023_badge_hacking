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

    float rotation = 0;

    
    while (true) {
        rotation += 0.01;
        std::vector<Shape> scene;

        scene.push_back(primitives::square);
        scene.back().rotate(rotation);
        scene.back().scale(0.5, 0.5);

        scene.push_back(primitives::square);
        scene.back().rotate(-rotation*2);
        scene.back().scale(0.4, 0.4);

        scene.push_back(primitives::square);
        scene.back().rotate(rotation*3);
        scene.back().scale(0.3, 0.3);

        scene.push_back(primitives::square);
        scene.back().rotate(-rotation*4);
        scene.back().scale(0.2, 0.2);

        scene.push_back(primitives::square);
        scene.back().rotate(rotation*4.5);
        scene.back().scale(0.1, 0.1);

        auto output_coords = rasterize(scene);

        dac::update_buffer(std::move(output_coords));

        vTaskDelay(pdMS_TO_TICKS(16));
    }
}
