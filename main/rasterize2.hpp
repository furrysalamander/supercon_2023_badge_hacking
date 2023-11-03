#pragma once

#include <vector>

const MIN_COORD = 0;
const MAX_COORD = 255;

void BresenhamLineAlgorithm(int32_t x1, int32_t y1, int32_t x2, int32_t y2, std::vector<float>& output) {
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        // This could be made more efficient by just skipping until points are on the screen
        if (x1 >= MIN_COORD && x1 <= MAX_COORD && y1 >= MIN_COORD && y1 <= MAX_COORD) {
            output.push_back(x1);
            output.push_back(y1);
        }

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }

    return;
}
