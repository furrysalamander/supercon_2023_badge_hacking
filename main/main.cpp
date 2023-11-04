#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <rtc_wdt.h>
#include <esp_task_wdt.h>
#include <math.h>
#include <vector>
#include <array>
#include <thread>

#include "point.h"
#include "uiDraw.hpp"

extern "C" void app_main(void)
{
    while (true) {
        UI::init();
        UI::drawMediumAsteroid(Point(0, 0), 0);
        UI::display();
    }
}
