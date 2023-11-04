#pragma once
#include <mat.h>
#include <vector>
#include <ranges>
#include <cstring>
#include <memory>

#include "composite.hpp"

class Shape {
public:
    Shape(std::vector<float> points, std::vector<std::array<size_t, 2>> edges) {
        for (auto i = 0; i < points.size(); i+=2) {
            this->points.emplace_back(dspm::Mat(2, 1));
            this->points.back()(0, 0) = points[i];
            this->points.back()(0, 1) = points[i + 1];
        }
        // this->edges = std::make_unique<std::vector<std::array<size_t, 2>>>(edges);
    }

    std::vector<dspm::Mat> points;
    // std::shared_ptr<std::vector<std::array<size_t, 2>>> edges;

    void rotate(float degrees) {
        auto rotation_matrix = comp::rotation(degrees);
        for (auto& point: points) {
            point *= *rotation_matrix;
        }
    }

    void translate(float x, float y) {
        auto translation_matrix = comp::translation(x, y);
        for (auto& point: points) {
            point += *translation_matrix;
        }
    }

    void scale(float x, float y) {
        auto scaling_matrix = comp::scaling(x, y);
        for (auto& point: points) {
            point *= *scaling_matrix;
        }
    }
};


