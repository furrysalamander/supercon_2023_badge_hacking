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

#include "rasterize.hpp"
#include "primitives.hpp"
#include "assets.hpp"

extern "C" void app_main(void)
{
    // dac::init_continuous_dac();
    dac::init_oneshot_dac();
    std::thread render_thread(dac::render_thread);

    float rotation = 0;

    while (true) {
        rotation += 0.01;
        // if (rotation > M_TWOPI) {
        //     rotation -= M_TWOPI;
        // }
        std::vector<Shape> scene;

        float scaling_factor = 0.2 * sin(rotation) + 1.0f;

        scene.push_back(primitives::square);
        scene.back().rotate(rotation);
        scene.back().scale(0.3, 0.3);
        scene.back().translate(-0.3, -0.3);
        scene.back().rotate(rotation*0.8);
        scene.back().scale(scaling_factor, scaling_factor);

        scene.push_back(primitives::square);
        scene.back().rotate(-rotation*1.5);
        scene.back().scale(0.3, 0.3);
        scene.back().translate(-0.3, 0.3);
        scene.back().rotate(rotation*0.8);
        scene.back().scale(scaling_factor, scaling_factor);

        scene.push_back(primitives::trapezoid);
        scene.back().rotate(rotation*2);
        scene.back().scale(0.3, 0.3);
        scene.back().translate(0.3, -0.3);
        scene.back().rotate(rotation*0.8);
        scene.back().scale(scaling_factor, scaling_factor);

        scene.push_back(primitives::square);
        scene.back().rotate(-rotation*2.5);
        scene.back().scale(0.3, 0.3);
        scene.back().translate(0.3, 0.3);
        scene.back().rotate(rotation*0.8);
        scene.back().scale(scaling_factor, scaling_factor);

        // scene.push_back(primitives::trapezoid);
        // scene.back().rotate(rotation*3);
        // scene.back().scale(0.3, 0.3);

        // std::printf("rotation: %f\n", rotation);

        scene.push_back(primitives::triangle);
        scene.back().rotate(-rotation*4);
        scene.back().scale(0.2, 0.2);

        // scene.push_back(primitives::square);
        // scene.back().rotate(rotation*4.5);
        // scene.back().scale(0.15, 0.15);

        // scene.push_back(primitives::square);
        // scene.back().rotate(-rotation*4.5);
        // scene.back().scale(0.1, 0.1);

        auto output_coords = rasterize(scene);
        // std::printf("output")
        // std::printf("%d, %d\n", (*output_coords)[0], (*output_coords)[1]);
        // output_coords->push_back(0.0f);
        // output_coords->push_back(0.0f);
        dac::update_buffer(std::move(output_coords));

        vTaskDelay(pdMS_TO_TICKS(5));
    }
}
