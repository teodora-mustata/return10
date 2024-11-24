#include "Bullet.h"

Bullet::Bullet(int startX, int startY, Direction dir, float bulletSpeed)
    : m_x(startX), m_y(startY), m_direction(dir), m_speed(bulletSpeed), m_active(true)
{
}

void Bullet::Move() {
    auto offset = DirectionUtils::toOffset(m_direction);
    m_x += static_cast<int>(offset.first * m_speed);
    m_y += static_cast<int>(offset.second * m_speed);
}

void Bullet::Deactivate() {
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


int Bullet::GetX() const
{
    return m_x;
}
int Bullet::GetY() const
{ 
    return m_y; 
}
Direction Bullet::GetDirection() const {
    return m_direction;
}
//float Bullet::getSpeed() const { return m_speed; }
bool Bullet::IsActive() const { 
    return m_active; 
}
void Bullet::SetX(int x)
{
    m_x = x;
}
void Bullet::SetY(int y) { 
    m_y = y; 
}
void Bullet::SetDirection(Direction direction) { 
    m_direction = direction; 
}
void Bullet::SetSpeed(float speed) { 
    m_speed = speed; 
}
void Bullet::SetActive(bool active) { 
    m_active = active; 
}
