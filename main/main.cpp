#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <thread>

#include "uiDraw.hpp"
#include "game.h"

extern "C" void app_main(void)
{
    // Set upt the game
    Point topLeft(-WORLD_SIZE, WORLD_SIZE);
    Point bottomRight(WORLD_SIZE, -WORLD_SIZE);
    Game game(topLeft, bottomRight);

    // Set up the display rendering thread
    UI::init();
    std::thread render_thread(dac::render_thread);

    for (auto shape : UI::scene) {
        for (auto point : shape.points) {
            std::printf("{%f, %f}", point[0], point[1]);
        }
        std::printf("\n");
    }
    
    while (true) {
        game.advance();
        game.draw();
        UI::display();
    }
}
