#include "render.hpp"
#include <driver/dac_continuous.h>
#include <driver/dac_oneshot.h>
#include <array>
#include <mutex>

#include <rtc_wdt.h>
#include <esp_task_wdt.h>

namespace dac {

std::unique_ptr<std::vector<std::array<uint8_t, 2>>> data;

dac_continuous_handle_t dac_output_handle = nullptr;

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

void update_buffer(std::unique_ptr<std::vector<std::array<uint8_t, 2>>> buffer) {
    std::printf("%d\n", buffer->size());

    // I found that if I didn't disable and reenable, the buffer was getting misaligned.  Still not sure exactly why.
    ESP_ERROR_CHECK(dac_continuous_disable(dac_output_handle));
    data = std::move(buffer);
    ESP_ERROR_CHECK(dac_continuous_enable(dac_output_handle));

    ESP_ERROR_CHECK(dac_continuous_write_cyclically(dac_output_handle, reinterpret_cast<uint8_t*>(data->data()), data->size()*2, NULL));
}

}