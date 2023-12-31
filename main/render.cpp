#include "render.hpp"
#include <driver/dac_continuous.h>

namespace dac {

std::unique_ptr<std::vector<uint8_t>> data;

dac_continuous_handle_t dac_output_handle = nullptr;

void init_dac() {
    // referencing 
    // https://github.com/espressif/esp-idf/blob/b4268c874a4cf8fcf7c0c4153cffb76ad2ddda4e/examples/peripherals/dac/dac_continuous/signal_generator/main/dac_continuous_example_dma.c#L58
    dac_continuous_config_t cont_cfg = {
        .chan_mask = DAC_CHANNEL_MASK_ALL,
        .desc_num = 8,
        // I think maybe this is just the max size?  If so, we don't need to re-init the dma stuff every time.
        .buf_size = 4092, 
        .freq_hz = 60000, // frequency at which data is written to the output
        .offset = 0,
        .clk_src = DAC_DIGI_CLK_SRC_DEFAULT,
        .chan_mode = DAC_CHANNEL_MODE_ALTER,
    };

    ESP_ERROR_CHECK(dac_continuous_new_channels(&cont_cfg, &dac_output_handle));
    ESP_ERROR_CHECK(dac_continuous_enable(dac_output_handle));
}

void update_buffer(std::unique_ptr<std::vector<uint8_t>> buffer) {
    data = std::move(buffer);
    ESP_ERROR_CHECK(dac_continuous_write_cyclically(dac_output_handle, data->data(), data->size(), NULL));
}

    // add_line std::array<uint8_t, 4>
}

