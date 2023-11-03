#pragma once
#include <mat.h>
#include <vector>

class Shape {
public:
    std::vector<float> points;
    std::unique_ptr<std::vector<std::array<size_t, 2>>> lines;
};


