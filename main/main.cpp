#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <rtc_wdt.h>
#include <esp_task_wdt.h>
#include <math.h>
#include <vector>
#include <array>
#include <thread>

#include "uiDraw.hpp"

extern "C" void app_main(void)
{
    UI::init();

    while (true) {
        UI::drawMediumAsteroid(Point(0, 0), 0);
        UI::display();
    }
}
