#pragma once
#include "Direction.h"
#include <chrono>
#include "DirectionUtils.h"
#include "Map.h"
#include "Player.h"
class Bullet
{
public:
    int x; 
    int y; 
    Direction direction; 
    float speed=0.25; 
    bool active; 
    std::chrono::time_point<std::chrono::steady_clock> fired_at; 

    Bullet(int startX, int startY, Direction dir, float speed);

    void move();
    bool checkPlayerCollision(Player& target);
    bool checkWallCollision(Map& map);
    void deactivate();
    //todo modify bullet speed
    //if speed==0.25 
};

