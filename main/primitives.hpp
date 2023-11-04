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
            this->points.emplace_back(2, 1);
            this->points.back()(0, 0) = points[i];
            this->points.back()(0, 1) = points[i + 1];
        }
        // this->edges = std::make_unique<std::vector<std::array<size_t, 2>>>(edges);
    }

    std::vector<dspm::Mat> points;
    // std::shared_ptr<std::vector<std::array<size_t, 2>>> edges;

    void rotate(float degrees) {
        static auto rotation_matrix = dspm::Mat(2, 2);
        comp::rotation(degrees, rotation_matrix);

        // std::printf("matrix: %f\n", rotation_matrix.data[0]);

        for (auto& point: points) {
            point = rotation_matrix * point;
        }

        // std::printf("matrix: %f\n", rotation_matrix.data[0]);
    }

    void translate(float x, float y) {
        static auto translation_matrix = dspm::Mat(2, 1);
        comp::translation(x, y, translation_matrix);

        for (auto& point: points) {
            point += translation_matrix;
        }
    }

    void scale(float x, float y) {
        static auto scaling_matrix = dspm::Mat(2, 2);
        comp::scaling(x, y, scaling_matrix);

        for (auto& point: points) {
            point = scaling_matrix * point;
        }
    }
};


