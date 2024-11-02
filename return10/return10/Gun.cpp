#include "Gun.h"

Gun::Gun() : lastFiredTime(std::chrono::steady_clock::now()) {}

bool Gun::fire(int playerX, int playerY, Direction playerDirection, float bulletSpeed)
{
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> timeSinceLastShot = now - lastFiredTime;

    if (timeSinceLastShot.count() >= firingRate.count())
    {
        Bullet newBullet(playerX, playerY, playerDirection, bulletSpeed);
        newBullet.active = true;
        newBullet.fired_at = now;

        firedBullets.push_back(newBullet);
        lastFiredTime = now;

        return true; //Fired
    }
    return false; // Not enough time has passed to fire again
}

std::vector<Bullet> Gun::getBullets() const //I deleted const ref because I need to acces the last bullet in player class
{
    return firedBullets; 
}

