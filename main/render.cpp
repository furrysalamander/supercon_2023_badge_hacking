#include "render.hpp"
#include <driver/dac_continuous.h>
#include <driver/dac_oneshot.h>
#include <array>
#include <mutex>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <rtc_wdt.h>
#include <esp_task_wdt.h>

namespace dac {

std::unique_ptr<std::vector<std::array<uint8_t, 2>>> data;
std::unique_ptr<std::vector<std::array<uint8_t, 2>>> data_real;
// std::mutex data_mutex;

dac_continuous_handle_t dac_output_handle = nullptr;

dac_oneshot_handle_t x_output_handle = nullptr;
dac_oneshot_handle_t y_output_handle = nullptr;

dac_oneshot_config_t x_config = {
    .chan_id = DAC_CHAN_0,
};
dac_oneshot_config_t y_config = {
    .chan_id = DAC_CHAN_1,
};

void init_oneshot_dac() {
    ESP_ERROR_CHECK(dac_oneshot_new_channel(&x_config, &x_output_handle));
    ESP_ERROR_CHECK(dac_oneshot_new_channel(&y_config, &y_output_handle));
}

dac_continuous_config_t cont_cfg = {
    .chan_mask = DAC_CHANNEL_MASK_ALL,
    .desc_num = 10,
    // I think maybe this is just the max size?  If so, we don't need to re-init the dma stuff every time.
    .buf_size = 4092, 
    .freq_hz = 60000, // frequency at which data is written to the output
    .offset = 0,
    .clk_src = DAC_DIGI_CLK_SRC_DEFAULT,
    .chan_mode = DAC_CHANNEL_MODE_ALTER,
};

void init_continuous_dac() {
    // referencing 
    // https://github.com/espressif/esp-idf/blob/b4268c874a4cf8fcf7c0c4153cffb76ad2ddda4e/examples/peripherals/dac/dac_continuous/signal_generator/main/dac_continuous_example_dma.c#L58

    ESP_ERROR_CHECK(dac_continuous_new_channels(&cont_cfg, &dac_output_handle));
    ESP_ERROR_CHECK(dac_continuous_enable(dac_output_handle));
}

void output_coord(std::array<uint8_t, 2> point) {
    ESP_ERROR_CHECK(dac_oneshot_output_voltage(x_output_handle, point[0]));
    ESP_ERROR_CHECK(dac_oneshot_output_voltage(y_output_handle, point[1]));
}

void update_buffer(std::unique_ptr<std::vector<std::array<uint8_t, 2>>> buffer) {
    // ESP_ERROR_CHECK(dac_continuous_write_cyclically(dac_output_handle, buffer->data(), buffer->size(), NULL));
    // std::unique_lock<std::mutex> lock(data_mutex);
    data_real = std::move(buffer);
}


void render_thread() {
    while (true) {
        vTaskDelay(1);
        // std::unique_lock<std::mutex> lock(data_mutex);
        // if (data) {
        //     data_real = std::move(data);
        // }
        // lock.unlock();

        if (data_real) {
            for (int i = 0; i < 10; i++) {
                for (const auto& point : *data_real) {
                    output_coord(point);
                }
            }
        }
    }
}
    // add_line std::array<uint8_t, 4>
}

