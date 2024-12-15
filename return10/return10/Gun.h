#pragma once
#include "Bullet.h"
#include "Direction.h"
#include <chrono>
#include <vector>
#include <algorithm>

class Gun
{
public:
    Gun();
    bool canFire() const;
    bool fire(int playerX, int playerY, Direction playerDirection, float bulletSpeed);

    std::vector<Bullet> getFiredBullets() const;
    std::chrono::duration<float> getFiringRate() const;
    float GetBulletSpeed() const;
    float GetFiringRate()const;

    void SetBulletSpeed(float newBulletSpeed);
    void setFiringRate(std::chrono::duration<float> newRate);

    void Jam(float duration);
    void UpdateJammed(float deltaTime);
    bool IsJammed() const;

private:
    std::chrono::duration<float> m_firingRate = std::chrono::seconds(4);
    std::chrono::time_point<std::chrono::steady_clock> m_lastFiredTime;
    std::vector<Bullet> m_firedBullets;
    float m_bulletSpeed = 0.25;
    bool m_isJammed = false;
    float m_jammedTimeRemaining = 0.0f;
};
