#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <thread>
#include <driver/gpio.h>

#include "uiDraw.hpp"
#include "game.h"

extern "C" void app_main(void)
{
    // Set up the game
    Point topLeft(-WORLD_SIZE, WORLD_SIZE);
    Point bottomRight(WORLD_SIZE, -WORLD_SIZE);
    Game game(topLeft, bottomRight);

    // Set up the display rendering thread
    UI::init();
    std::thread render_thread(dac::render_thread);

    gpio_set_direction(GPIO_LEFT, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_RIGHT, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_SHOOT, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_FORWARD, GPIO_MODE_INPUT);

    // Get the interface ready
    Interface ui("Asteroids", topLeft, bottomRight);

    // Draw the first frame on the screen
    game.draw();

    // Hold game until we start shooting or launching
    while (!(Interface::isSpacePress || Interface::isUpPress)) {
        Interface::isSpacePress = !(int)gpio_get_level(GPIO_SHOOT);
        Interface::isUpPress = !(int)gpio_get_level(GPIO_FORWARD);
    }
    
    // Run game loop
    while (true) {
        game.advance();
        Interface::isLeftPress = !(int)gpio_get_level(GPIO_LEFT);
        Interface::isRightPress = !(int)gpio_get_level(GPIO_RIGHT);
        Interface::isSpacePress = !(int)gpio_get_level(GPIO_SHOOT);
        Interface::isUpPress = !(int)gpio_get_level(GPIO_FORWARD);
        game.handleInput(ui);
        game.draw();
        UI::display();
    }
}
