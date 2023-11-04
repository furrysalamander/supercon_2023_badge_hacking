#pragma once
#include <mat.h>

namespace comp
{
    std::unique_ptr<dspm::Mat> rotation(float degrees) {
        const auto cos_d = cos(degrees);
        const auto sin_d = sin(degrees);

        auto matrix = std::make_unique<dspm::Mat>(2, 2);
        (*matrix)(0, 0) = cos_d;
        (*matrix)(0, 1) = -sin_d;
        (*matrix)(1, 0) = sin_d;
        (*matrix)(1, 1) = cos_d;

        return matrix;
    }

    std::unique_ptr<dspm::Mat> scaling(float x, float y) {
        auto matrix = std::make_unique<dspm::Mat>(2, 2);
        (*matrix)(0, 0) = x;
        (*matrix)(1, 1) = y;

        return matrix;
    }

    std::unique_ptr<dspm::Mat> translation(float x, float y) {
        auto matrix = std::make_unique<dspm::Mat>(2, 1);
        (*matrix)(0, 0) = x;
        (*matrix)(1, 0) = y;
        return matrix;
    }
}
