#pragma once
#include "Direction.h"
#include <chrono>
#include "DirectionUtils.h"
#include "Map.h"
class Bullet
{
public:
    int x; 
    int y; 
    Direction direction; 
    float speed; 
    bool active; 
    std::chrono::time_point<std::chrono::steady_clock> fired_at; 

    Bullet(int startX, int startY, Direction dir, float speed);

    void move();
    void deactivate();
};

