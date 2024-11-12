#pragma once
#include "Direction.h"
#include <chrono>
#include "DirectionUtils.h"
#include "CellType.h"

class Bullet
{
public:
    int m_x;
    int m_y;
    Direction m_direction;
    float m_speed = 0.25;
    bool m_active;
    //std::chrono::time_point<std::chrono::steady_clock> m_fired_at;
    std::chrono::time_point<std::chrono::steady_clock> m_fired_at;

    Bullet(int startX, int startY, Direction dir, float speed);

    void move();
    //to do move to game logic
    bool checkPlayerCollision(Player& target);
    bool checkWallCollision(Map& map);
    void deactivate();
    void duplicateBulletSpeed(const Player& player);
    void givePoints(Player& player);
    void removePlayer(Player& player);
};


