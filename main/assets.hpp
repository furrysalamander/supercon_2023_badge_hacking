#pragma once
#include "primitives.hpp"
#include <memory>

namespace primitives {
    const auto square = Shape {
        {
            -1.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, -1.0f,
            -1.0f, -1.0f,
        },
        // syntax for initializing non-circular shapes (custom edge list)
        // std::make_unique<std::vector<std::array<size_t, 2>>>(std::vector {0, 1}),
    };

    const auto triangle = Shape {
        {
            0.0f, 1.0f,
            -1.0f, -1.0f,
            1.0f, -1.0f,
        },
    };

    const auto trapezoid = Shape {
        {
            -0.5f, 1.0f,
            0.5f, 1.0f,
            1.0f, -1.0f,
            -1.0f, -1.0f,
        },
    };
}

namespace asteroids {

}