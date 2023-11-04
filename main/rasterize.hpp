#pragma once
#include "primitives.hpp"

#include <vector>
#include <memory>
#include <render.hpp>

const auto MIN_COORD = 0;
const auto MAX_COORD = 255;

void BresenhamLineAlgorithm(int32_t x1, int32_t y1, int32_t x2, int32_t y2, std::vector<std::array<uint8_t, 2>>& output) {
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    // std::printf("point 1: %ld, %ld point 2: %ld, %ld\n", x1, y1, x2, y2);

    while (true) {
        // This could be made more efficient by just skipping until points are on the screen
        if (x1 >= MIN_COORD && x1 <= MAX_COORD && y1 >= MIN_COORD && y1 <= MAX_COORD) {
            // std::printf("x: %ld, y: %ld\n", x1, y1);
            // std::printf("%ld", x1);
            // output.push_back(x1);
            // output.push_back(y1);
            output.push_back({static_cast<uint8_t>(x1), static_cast<uint8_t>(y1)});
            output.push_back({static_cast<uint8_t>(x1), static_cast<uint8_t>(y1)});
            output.push_back({static_cast<uint8_t>(x1), static_cast<uint8_t>(y1)});
            // dac::output_coord({static_cast<uint8_t>(x1), static_cast<uint8_t>(y1)});
            // break;
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

std::unique_ptr<std::vector<std::array<uint8_t, 2>>> rasterize(std::vector<Shape>& elements) {
    auto output_buffer = std::make_unique<std::vector<std::array<uint8_t, 2>>>();

    for (auto& shape : elements) {
        // If I get segment lists implemented...
        // for (const auto& segment : *shape.lines) {
            // tmp_a = shape.points[segment[0]*2];
            // tmp_b = shape.points[segment[0]*2 + 1];
            // tmp_c = shape.points[segment[1]*2];
            // tmp_d = shape.points[segment[1]*2 + 1];

        for (auto& point : shape.points) {
            for (auto& coord : point) {
                coord += 1;
                coord *= 128;
            }
        }

        // Make the points list circular
        shape.points.push_back(shape.points[0]);
        // std::printf("num_points: %d\n", shape.points.size());
        // std::printf("test: %f\n", shape.points[0](0,0));

        for (size_t i = 0; i < shape.points.size() - 1; i++) {
            // std::printf("point 1: %f, %f point 2: %f, %f\n", shape.points[i](0, 0), shape.points[i](1, 0), shape.points[i+1](0, 0), shape.points[i+1](1, 0));
            BresenhamLineAlgorithm(shape.points[i][0], shape.points[i][1], shape.points[i+1][0], shape.points[i+1][1], *output_buffer);
        }
        // std::printf("\n");
    }

    // for (auto& x : *output_buffer) {
    //     // std::printf("val: %d\n", x);
    // }

    return output_buffer;
}