#pragma once
#include "primitives.hpp"

#include <vector>
#include <memory>
#include <render.hpp>

std::unique_ptr<std::vector<std::array<uint8_t, 2>>> rasterize(std::vector<Shape>& elements);
