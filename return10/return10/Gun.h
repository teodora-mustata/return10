#pragma once
#include "Bullet.h"
#include "Direction.h"
#include <chrono>
#include <vector>

class Gun
{
private:
    const float firing_rate = 0;
    std::chrono::time_point<std::chrono::steady_clock> last_fired_time;
    std::vector<Bullet> fired_bullets;

public:
    Gun();
    bool fire(int playerX, int playerY, Direction playerDirection, float bulletSpeed);
    const std::vector<Bullet>& getBullets() const;
};
