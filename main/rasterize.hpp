#pragma once
#include "primitives.hpp"

#include <vector>
#include <memory>

#include <dsps_mulc.h>
#include <dsps_addc.h>

std::unique_ptr<std::vector<uint8_t>> rasterize(std::vector<Shape>& elements) {
    for (auto& shape : elements) {
        // If I get segment lists implemented...
        // for (const auto& segment : *shape.lines) {
            // tmp_a = shape.points[segment[0]*2];
            // tmp_b = shape.points[segment[0]*2 + 1];
            // tmp_c = shape.points[segment[1]*2];
            // tmp_d = shape.points[segment[1]*2 + 1];
        
        ESP_ERROR_CHECK(dsps_addc_f32_ae32(shape.points.data(), shape.points.data(), shape.points.size(), 1));
        ESP_ERROR_CHECK(dsps_mulc_f32_ae32(shape.points.data(), shape.points.data(), shape.points.size(), 128));
        // Make the points list circular
        shape.points.push_back(shape.points[0]);
        shape.points.push_back(shape.points[1]);
        for (size_t i = 0; i < shape.points.size(); i += 2) {
            int32_t x1 = shape.points[i] * 255;
            int32_t y1 = shape.points[i+1] * 255;
            int32_t x2 = shape.points[i] * 255;
            int32_t y2 = shape.points[i+1] * 255;
        }
    }
    return nullptr;
}