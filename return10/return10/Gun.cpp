#include "Gun.h"

Gun::Gun() : m_lastFiredTime(std::chrono::steady_clock::now()) {}


bool Gun::canFire() const
{
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration<float>(now - m_lastFiredTime) >= m_firingRate;
}

void Gun::Jam(std::chrono::duration<float> duration) {
    m_isJammed = true;
    m_jammedEndTime = std::chrono::steady_clock::now() + std::chrono::duration_cast<std::chrono::steady_clock::duration>(duration);
}

void Gun::UpdateJammed() {
    if (m_isJammed && std::chrono::steady_clock::now() >= m_jammedEndTime) {
        m_isJammed = false;
    }
}

bool Gun::IsJammed() const {
    return m_isJammed;
}

bool Gun::fire(int playerX, int playerY, Direction playerDirection) {

    if (!m_isJammed && canFire()) {
        
        // Calculăm timpul scurs de la ultima tragere
        auto now = steady_clock::now();
        if (duration_cast<seconds>(now - m_lastFiredTime).count() < 4) {
            return false; // Așteptăm 4 secunde între trageri
        }

        int bulletX = playerX;
        int bulletY = playerY;

        switch (playerDirection) {
        case Direction::UP: bulletY -= 1; break;
        case Direction::DOWN: bulletY += 1; break;
        case Direction::LEFT: bulletX -= 1; break;
        case Direction::RIGHT: bulletX += 1; break;
        default: break;
        }

        Bullet newBullet(playerX, playerY, playerDirection, m_bulletSpeed);
        newBullet.SetActive(true);

        m_firedBullets.push_back(newBullet);
        m_lastFiredTime = std::chrono::steady_clock::now();

        return true; // Fired
    }
    return false; // Gun is jammed or firing rate not met
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

