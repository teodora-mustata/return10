#include "Bullet.h"

Bullet::Bullet(int startX, int startY, Direction dir, float bulletSpeed)
    : m_x(startX), m_y(startY), m_direction(dir), m_speed(bulletSpeed), m_active(true)
{
}

void Bullet::move() {
    auto offset = DirectionUtils::toOffset(m_direction);
    m_x += static_cast<int>(offset.first * m_speed);
    m_y += static_cast<int>(offset.second * m_speed);
}

void Bullet::deactivate() {
    m_active = false;
}

//void Bullet::duplicateBulletSpeed()
//{
//    this->m_speed = m_speed * 2;
//}

//void Bullet::givePoints(Player& player)
//{
//    //to do daca a si castigat meciul ar trebui sa primeasca inca 200
//    player.addPoints(100);
//}

//void Bullet::removePlayer(Player& player)
//{
//    //to do
//}


int Bullet::getX() const
{
    return m_x;
}
int Bullet::getY() const
{ 
    return m_y; 
}
Direction Bullet::getDirection() const { return m_direction; }
//float Bullet::getSpeed() const { return m_speed; }
bool Bullet::isActive() const { return m_active; }
void Bullet::setX(int x)
{
    m_x = x;
}
void Bullet::setY(int y) { m_y = y; }
void Bullet::setDirection(Direction direction) { m_direction = direction; }
void Bullet::setSpeed(float speed) { m_speed = speed; }
void Bullet::setActive(bool active) { m_active = active; }
