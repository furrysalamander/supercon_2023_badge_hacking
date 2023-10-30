#pragma once
#include <mat.h>
#include <vector>

class shape {
public:
    std::vector<dspm::Mat> points;
    std::unique_ptr<std::vector<std::array<size_t, 2>>> lines;
};


