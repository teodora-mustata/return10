#include "Gun.h"

Gun::Gun() : m_lastFiredTime(std::chrono::steady_clock::now()) {}

bool Gun::fire(int playerX, int playerY, Direction playerDirection, float bulletSpeed)
{
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> timeSinceLastShot = now - m_lastFiredTime;

    if (timeSinceLastShot.count() >= m_firingRate.count())
    {
        Bullet newBullet(playerX, playerY, playerDirection, bulletSpeed);
        newBullet.setActive(true);
        //newBullet.m_fired_at = now;

        m_firedBullets.push_back(newBullet);
        m_lastFiredTime = now;

        return true; //Fired
    }
    return false; // Not enough time has passed to fire again
}



std::vector<Bullet> Gun::getFiredBullets() const //I deleted const ref because I need to acces the last bullet in player class
{
    return m_firedBullets; 
}

std::chrono::duration<float> Gun::getFiringRate() const
{
    return m_firingRate;
}

void Gun::setFiringRate(std::chrono::duration<float> newRate)
{
    m_firingRate = newRate;
}

float Gun::GetBulletSpeed() const
{
    return m_bulletSpeed;
}

void Gun::SetBulletSpeed(float newBulletSpeed)
{
    m_bulletSpeed = newBulletSpeed;
}

