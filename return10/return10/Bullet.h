#pragma once
#include "Direction.h"
#include <chrono>
#include "DirectionUtils.h"
//#include "CellType.h"

class Bullet
{
public:
    Bullet(int startX, int startY, Direction dir, float bulletSpeed);
    void Move();
    void Deactivate();
    int GetX() const;
    int GetY() const;
    Direction GetDirection() const;
    bool IsActive() const;

    // Setters
    void SetX(int x);
    void SetY(int y);
    void SetDirection(Direction direction);
    void SetSpeed(float speed);
    void SetActive(bool active);

private:
    int m_x;
    int m_y;
    Direction m_direction;
    bool m_active;
    float m_speed;
};


