#include "Gun.h"

Gun::Gun() : last_fired_time(std::chrono::steady_clock::now()) {}

bool Gun::fire(int playerX, int playerY, Direction playerDirection, float bulletSpeed)
{
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> time_since_last_shot = now - last_fired_time;

    if (time_since_last_shot.count() >= firing_rate)
    {
        Bullet new_bullet(playerX, playerY, playerDirection, bulletSpeed);
        new_bullet.active = true;
        new_bullet.fired_at = now;

        fired_bullets.push_back(new_bullet);
        last_fired_time = now;

        return true; //Fired
    }
    return false; // Not enough time has passed to fire again
}

const std::vector<Bullet>& Gun::getBullets() const
{
    return fired_bullets;
}

