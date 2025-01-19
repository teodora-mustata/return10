#include "Gun.h"

Gun::Gun() : m_lastFiredTime(std::chrono::steady_clock::now()) {}


bool Gun::canFire() const
{
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration<float>(now - m_lastFiredTime) >= m_firingRate;
}

void Gun::jam(std::chrono::duration<float> duration) {
    m_isJammed = true;
    m_jammedEndTime = std::chrono::steady_clock::now() + std::chrono::duration_cast<std::chrono::steady_clock::duration>(duration);
}

void Gun::updateJammed() {
    if (m_isJammed && std::chrono::steady_clock::now() >= m_jammedEndTime) {
        m_isJammed = false;
    }
}

bool Gun::isJammed() const {
    return m_isJammed;
}

bool Gun::fire(int playerX, int playerY, Direction playerDirection) {

    if (m_isJammed || !canFire()) {
        return false;
    }

    int bulletX = playerX;
    int bulletY = playerY;

    Bullet newBullet(bulletX, bulletY, playerDirection, m_bulletSpeed);
    newBullet.setActive(true);

    m_firedBullets.push_back(newBullet);
    std::cout << "bullet fired at position (" << bulletX << ", " << bulletY << ")" << std::endl;

    return true;
}



std::vector<Bullet> Gun::getFiredBullets() const
{
    return m_firedBullets; 
}

std::vector<Bullet>& Gun::getFiredBullets()
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

float Gun::getBulletSpeed() const
{
    return m_bulletSpeed;
}

void Gun::setBulletSpeed(float newBulletSpeed)
{
    if (newBulletSpeed <= 0) {
        throw std::invalid_argument("Bullet speed must be > 0.");
    }
    m_bulletSpeed = newBulletSpeed;
}

float Gun::GetFiringRate() const
{
    return m_firingRate.count();
}

