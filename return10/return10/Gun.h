#pragma once
#include "Bullet.h"
#include "Direction.h"
#include <chrono>
#include <vector>
#include <algorithm>

class Gun
{
private:
    std::chrono::duration<float> m_firingRate = std::chrono::seconds(4);
    std::chrono::time_point<std::chrono::steady_clock> m_lastFiredTime;
    std::vector<Bullet> m_firedBullets;
public:
    Gun();
    bool fire(int playerX, int playerY, Direction playerDirection, float bulletSpeed);
    std::vector<Bullet> getBullets() const;
};
