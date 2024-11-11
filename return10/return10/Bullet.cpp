
#include "Bullet.h"

Bullet::Bullet(int startX, int startY, Direction dir, float speed)
    : m_x(startX), m_y(startY), m_direction(dir), m_speed(speed), m_active(true)
{
}


bool Bullet::checkPlayerCollision(Player& target) {
    int targetX = target.GetPosition().first;
    int targetY = target.GetPosition().second;

    if (m_x == targetX && m_y == targetY && target.GetLives() > 1) {
        target.resetPosition();
        deactivate();
        target.loseLife();
        return true;
    }
    else {
        removePlayer(target);
    }
    return false;
}

bool Bullet::checkWallCollision(Map& map) {
    CellType cell = map.GetCellType(m_x, m_y);
    if (auto* wall = std::get_if<Wall>(&cell)) {
        if (wall->IsDestructible()) {
            map.SetCellType(m_x, m_y, std::monostate{});
            deactivate();
            return true;
        }
        else {
            deactivate();
            return true;
        }
    }
    return false;
}

void Bullet::move() {
    auto offset = DirectionUtils::toOffset(m_direction);
    m_x += static_cast<int>(offset.first * m_speed);
    m_y += static_cast<int>(offset.second * m_speed);
}

void Bullet::deactivate() {
    m_active = false;
}

void Bullet::duplicateBulletSpeed(const Player& player)
{
    if (true && m_speed == 0.25)//player.GetScore>=10
    {
        this->m_speed = m_speed * 2;
    }
}

void Bullet::givePoints(Player& player)
{
    //to do daca a si castigat meciul ar trebui sa primeasca inca 200
    player.addPoints(100);
}

void Bullet::removePlayer(Player& player)
{
    //to do
}
