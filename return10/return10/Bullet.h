#pragma once
#include "Direction.h"
#include <chrono>
#include "DirectionUtils.h"
#include "CellType.h"

class Bullet
{
private:
    int m_x;
    int m_y;
    Direction m_direction;
    float m_speed = 0.25;
    bool m_active;
    //std::chrono::time_point<std::chrono::steady_clock> m_fired_at;
    //std::chrono::time_point<std::chrono::steady_clock> m_fired_at;
public:
    Bullet(int startX, int startY, Direction dir, float speed);
    void move();
    void deactivate();
    void duplicateBulletSpeed();
    /*void givePoints(Player& player);
    void removePlayer(Player& player);*/


    int getX() const;
    int getY() const;
    Direction getDirection() const;
    float getSpeed() const;
    bool isActive() const;

    // Setters
    void setX(int x);
    void setY(int y);
    void setDirection(Direction direction);
    void setSpeed(float speed);
    void setActive(bool active);
};


