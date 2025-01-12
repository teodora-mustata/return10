#pragma once
#include "Direction.h"
#include <chrono>
#include "DirectionUtils.h"
//#include "CellType.h"

class Bullet
{
public:
    Bullet(int startX, int startY, Direction dir, float bulletSpeed);
    void move();
    void deactivate();
    int getX() const;
    int getY() const;
    Direction getDirection() const;
    bool isActive() const;

    
    void setX(int x);
    void setY(int y);
    void setDirection(Direction direction);
    void setSpeed(float speed);
    void setActive(bool active);

private:
    int m_x;
    int m_y;
    Direction m_direction;
    bool m_active;
    float m_speed;
};


