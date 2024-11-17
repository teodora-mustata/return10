#include "Gun.h"

Gun::Gun() : m_lastFiredTime(std::chrono::steady_clock::now()) {}

bool Gun::fire(int playerX, int playerY, Direction playerDirection, float bulletSpeed)
{
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> timeSinceLastShot = now - m_lastFiredTime;

    if (timeSinceLastShot.count() >= m_firingRate.count())
    {
        Bullet newBullet(playerX, playerY, playerDirection, bulletSpeed);
        newBullet.m_active = true;
        newBullet.m_fired_at = now;

        m_firedBullets.push_back(newBullet);
        m_lastFiredTime = now;

        return true; //Fired
    }
    return false; // Not enough time has passed to fire again
}



std::vector<Bullet> Gun::getBullets() const //I deleted const ref because I need to acces the last bullet in player class
{
    return m_firedBullets; 
}

