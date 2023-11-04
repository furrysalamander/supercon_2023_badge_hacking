#pragma once
#include <mat.h>

namespace comp
{
    dspm::Mat rotation(float degrees) {
        auto matrix = dspm::Mat(2, 2);

        const auto cos_d = cos(degrees);
        const auto sin_d = sin(degrees);

        matrix(0, 0) = cos_d;
        matrix(0, 1) = -sin_d;
        matrix(1, 0) = sin_d;
        matrix(1, 1) = cos_d;

        return matrix;
    }

    dspm::Mat scaling(float x, float y) {
        auto matrix = dspm::Mat(2, 2);

        matrix(0, 0) = x;
        matrix(1, 1) = y;

        return matrix;
    }

    dspm::Mat translation(float x, float y) {
        auto matrix = dspm::Mat(2, 1);

        matrix(0, 0) = x;
        matrix(1, 0) = y;

        return matrix;
    }
}
