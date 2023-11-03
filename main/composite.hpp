#pragma once
#include <mat.h>

namespace comp
{
    dspm::Mat rotate(float degrees)
    {
        const auto cos_d = cos(degrees);
        const auto sin_d = sin(degrees);
        float matrix[] = {
            cos_d, -sin_d,
            sin_d, cos_d,
        };

        return dspm::Mat(matrix, 2, 2);
    }

}
