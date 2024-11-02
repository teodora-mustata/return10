#pragma once
#include "Bullet.h"
#include "Direction.h"
#include <chrono>
#include <vector>

class Gun
{
private:
    std::chrono::duration<float> firingRate = std::chrono::seconds(4);
    std::chrono::time_point<std::chrono::steady_clock> lastFiredTime;
    std::vector<Bullet> firedBullets;

public:
    Gun();
    bool fire(int playerX, int playerY, Direction playerDirection, float bulletSpeed);
    std::vector<Bullet> getBullets() const;
};
