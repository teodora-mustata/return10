#include "Gun.h"

Gun::Gun() : m_lastFiredTime(std::chrono::steady_clock::now()) {}


bool Gun::canFire() const
{
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration<float>(now - m_lastFiredTime) >= m_firingRate;
}

void Gun::Jam(float duration) {
    m_isJammed = true;
    m_jammedTimeRemaining = duration;
}

void Gun::UpdateJammed(float deltaTime) {
    if (m_isJammed) {
        m_jammedTimeRemaining -= deltaTime;
        if (m_jammedTimeRemaining <= 0) {
            m_isJammed = false;
            m_jammedTimeRemaining = 0.0f;
        }
    }
}

bool Gun::IsJammed() const {
    return m_isJammed;
}

bool Gun::fire(int playerX, int playerY, Direction playerDirection, float bulletSpeed) {
    if (!m_isJammed && canFire()) {
        Bullet newBullet(playerX, playerY, playerDirection, bulletSpeed);
        newBullet.SetActive(true);

        m_firedBullets.push_back(newBullet);
        m_lastFiredTime = std::chrono::steady_clock::now();

        return true; // Fired
    }
    return false; // Gun is jammed or firing rate not met
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
    if (newRate <= std::chrono::duration<float>(0)) {
        throw std::invalid_argument("Firing rate cannot be instant.");
    }
    m_firingRate = newRate;
}

float Gun::GetBulletSpeed() const
{
    return m_bulletSpeed;
}

void Gun::SetBulletSpeed(float newBulletSpeed)
{
    if (newBulletSpeed <= 0) {
        throw std::invalid_argument("Bullet speed must be > 0.");
    }
    m_bulletSpeed = newBulletSpeed;
}

float Gun::GetFiringRate() const
{
    return m_firingRate.count();  // Returneaz numarul de secunde ca float
}

