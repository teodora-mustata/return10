#pragma once
#include <utility>
#include "Direction.h"
class DirectionUtils {
public:
    static std::pair<int, int> toOffset(Direction dir) {
        switch (dir) {
        case Direction::UP: return { 0, -1 };
        case Direction::DOWN: return { 0, 1 };
        case Direction::LEFT: return { -1, 0 };
        case Direction::RIGHT: return { 1, 0 };
        default: return { 0, 0 };
        }
    }
};

