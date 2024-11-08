#pragma once
#include "Bullet.h"
#include "Direction.h"
#include <chrono>
#include <vector>
#include <algorithm>
#include "Bullet.h"
#include "Map.h"

class Gun
{
private:
    std::chrono::duration<float> m_firingRate = std::chrono::seconds(4);
    std::chrono::time_point<std::chrono::steady_clock> m_lastFiredTime;
    std::vector<Bullet> m_firedBullets;
public:
    Gun();
    bool fire(int playerX, int playerY, Direction playerDirection, float bulletSpeed);
    void updateBullets(Map& map, Player& target);
    std::vector<Bullet> getBullets() const;
};
