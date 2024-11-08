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

//checks to see status of bullets and removes any inactive bullets that have collided from the m_firedBullets vector
//method called 
void Gun::updateBullets(Map& map, Player& target)
{   //needs to stay with iterator not range base because by removing from the vector it messes up the range base type for
    //need to choose where to call this and where if continous or maybe change it to once we see bullet collided somewhere else sent the message to 
    //simply erase not sure yet
    for (auto currentBullet = m_firedBullets.begin(); currentBullet != m_firedBullets.end(); ) {
        currentBullet->checkPlayerCollision(target);
        currentBullet->checkWallCollision(map);

        if (!currentBullet->m_active) {
            // if erased put iterator one place back because erase sets it further
            currentBullet = m_firedBullets.erase(currentBullet);
        }
        else {
            ++currentBullet; // only increment if we didnt erase
        }
    }

}

std::vector<Bullet> Gun::getBullets() const //I deleted const ref because I need to acces the last bullet in player class
{
    return m_firedBullets; 
}

