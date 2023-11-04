#pragma once
#include <vector>
#include <ranges>
#include <cstring>
#include <memory>
#include <math.h>


class Shape {
public:
    Shape(std::vector<float> points) {
        for (auto i = 0; i < points.size(); i+=2) {
            this->points.push_back({points[i], points[i+1]});
        }
        // this->edges = std::make_unique<std::vector<std::array<size_t, 2>>>(edges);
    }

    std::vector<std::array<float, 2>> points;
    // std::shared_ptr<std::vector<std::array<size_t, 2>>> edges;

    void rotate(float degrees) {
        const auto cos_d = cos(degrees);
        const auto sin_d = sin(degrees);

        for (auto& point: points) {
            const auto tmp_x = point[0];
            const auto tmp_y = point[1];
            point[0] = tmp_x * cos_d - tmp_y * sin_d;
            point[1] = tmp_x * sin_d + tmp_y * cos_d;
        }
    }

    void translate(float x, float y) {
        for (auto& point: points) {
            point[0] += x;
            point[1] += y;
        }
    }

    void scale(float x, float y) {
        for (auto& point: points) {
            point[0] *= x;
            point[1] *= y;
        }
    }
};


