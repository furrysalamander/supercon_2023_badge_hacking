#pragma once
#include "primitives.hpp"

#include <vector>
#include <memory>

#include <dsps_mulc.h>
#include <dsps_addc.h>

const auto MIN_COORD = 0;
const auto MAX_COORD = 255;

void BresenhamLineAlgorithm(int32_t x1, int32_t y1, int32_t x2, int32_t y2, std::vector<float>& output) {
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        // This could be made more efficient by just skipping until points are on the screen
        if (x1 >= MIN_COORD && x1 <= MAX_COORD && y1 >= MIN_COORD && y1 <= MAX_COORD) {
            output.push_back(x1);
            output.push_back(y1);
        }

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }

    return;
}

std::unique_ptr<std::vector<uint8_t>> rasterize(std::vector<Shape>& elements) {
    for (auto& shape : elements) {
        // If I get segment lists implemented...
        // for (const auto& segment : *shape.lines) {
            // tmp_a = shape.points[segment[0]*2];
            // tmp_b = shape.points[segment[0]*2 + 1];
            // tmp_c = shape.points[segment[1]*2];
            // tmp_d = shape.points[segment[1]*2 + 1];
        
        ESP_ERROR_CHECK(dsps_addc_f32_ae32(shape.points.data(), shape.points.data(), shape.points.size(), 1, 1, 1));
        ESP_ERROR_CHECK(dsps_mulc_f32_ae32(shape.points.data(), shape.points.data(), shape.points.size(), 128, 1, 1));
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