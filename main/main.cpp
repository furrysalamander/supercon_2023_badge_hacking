#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "uiDraw.hpp"

extern "C" void app_main(void)
{
    UI::init();
    auto rotation = 0.1;
    while (true) {
        rotation += 0.1;
        UI::drawMediumAsteroid(Point(0, 0), -rotation);
        UI::drawShip(Point(0, 0), rotation);
        UI::display();
    }
}
