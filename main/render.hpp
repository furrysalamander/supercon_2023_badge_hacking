#pragma once
#include <driver/dac_continuous.h>

#include <memory>
#include <vector>

namespace dac
{
    std::unique_ptr<std::vector<uint8_t>> data;
    dac_continuous_handle_t dac_output_handle = nullptr;
    void update_buffer(std::unique_ptr<std::vector<uint8_t>>& buffer)
    {
        if (dac_output_handle != nullptr)
        {
            ESP_ERROR_CHECK(dac_continuous_del_channels(dac_output_handle));
        }
        data = std::move(buffer);
        // referencing
        // https://github.com/espressif/esp-idf/blob/b4268c874a4cf8fcf7c0c4153cffb76ad2ddda4e/examples/peripherals/dac/d
        dac_continuous_config_t cont_cfg = {
            .chan_mask = DAC_CHANNEL_MASK_ALL,
            .desc_num = 8,
            // I think maybe this is just the max size? If so, we don't need to re-init the dma stuff every time. data->size(),
            .buf_size = data->size(),
            .freq_hz = 200000, // frequency at which data is written to the output
            .offset = 0,
            .clk_src = DAC_DIGI_CLK_SRC_DEFAULT,
            .chan_mode = DAC_CHANNEL_MODE_ALTER,
        };
        ESP_ERROR_CHECK(dac_continuous_new_channels(&cont_cfg, &dac_output_handle));
        ESP_ERROR_CHECK(dac_continuous_enable(dac_output_handle));
        ESP_ERROR_CHECK(dac_continuous_write_cyclically(dac_output_handle, data->data(), data->size(), NULL));
    }
}