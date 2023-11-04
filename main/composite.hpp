#pragma once
#include <mat.h>

namespace comp
{
    inline void rotation(float degrees, dspm::Mat& matrix) {
        const auto cos_d = cos(degrees);
        const auto sin_d = sin(degrees);

        matrix(0, 0) = cos_d;
        matrix(0, 1) = -sin_d;
        matrix(1, 0) = sin_d;
        matrix(1, 1) = cos_d;

        return;
    }

    inline void scaling(float x, float y, dspm::Mat& matrix) {
        matrix(0, 0) = x;
        matrix(1, 1) = y;
    }

    inline void translation(float x, float y, dspm::Mat& matrix) {
        matrix(0, 0) = x;
        matrix(1, 0) = y;
    }
}
