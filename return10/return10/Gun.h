#pragma once
#include "Bullet.h"
#include "Direction.h"
#include <chrono>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std::chrono;

class Gun
{
public:
    Gun();
    bool canFire() const;
    bool fire(int playerX, int playerY, Direction playerDirection);

    std::vector<Bullet> getFiredBullets() const;
    std::vector<Bullet>& getFiredBullets();

    std::chrono::duration<float> getFiringRate() const;
    float getBulletSpeed() const;
    float GetFiringRate()const;

    void setBulletSpeed(float newBulletSpeed);
    void setFiringRate(std::chrono::duration<float> newRate);

    void jam(std::chrono::duration<float> duration);
    void updateJammed();
    bool isJammed() const;

private:
    std::chrono::duration<float> m_firingRate = std::chrono::seconds(4);
    std::chrono::time_point<std::chrono::steady_clock> m_lastFiredTime;
    std::vector<Bullet> m_firedBullets;
    float m_bulletSpeed = 0.25;
    bool m_isJammed = false;
    float m_jammedTimeRemaining = 0.0f;
    std::chrono::time_point<std::chrono::steady_clock> m_jammedEndTime;
};
