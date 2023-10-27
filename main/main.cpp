#include <math.h>
#include <driver/dac_cosine.h>

#include <vector>
// #include <thread>
// #include <chrono>

extern "C" {
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
}

// using namespace std::chrono_literals;

extern "C" void app_main(void)
{
    dac_cosine_handle_t x_channel_handle;
    dac_cosine_config_t x_config = {
        .chan_id = DAC_CHAN_0,
        .freq_hz = 1000, // It will be covered by 8000 in the latter configuration
        .clk_src = DAC_COSINE_CLK_SRC_DEFAULT,
        .atten = DAC_COSINE_ATTEN_DEFAULT,
        .phase = DAC_COSINE_PHASE_0,
        .offset = 0,
    };
    x_config.flags.force_set_freq = false;

    dac_cosine_handle_t y_channel_handle;
    dac_cosine_config_t y_config = {
        .chan_id = DAC_CHAN_1,
        .freq_hz = 8000,
        .clk_src = DAC_COSINE_CLK_SRC_DEFAULT,
        .atten = DAC_COSINE_ATTEN_DB_6,
        .phase = DAC_COSINE_PHASE_180,
        .offset = 0,
    };
    y_config.flags.force_set_freq = true;


    ESP_ERROR_CHECK(dac_cosine_new_channel(&x_config, &x_channel_handle));
    ESP_ERROR_CHECK(dac_cosine_new_channel(&y_config, &y_channel_handle));

    ESP_ERROR_CHECK(dac_cosine_start(x_channel_handle));
    ESP_ERROR_CHECK(dac_cosine_start(y_channel_handle));

    while (1) {
        // std::this_thread::sleep_for(1ms);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
