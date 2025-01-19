#include "Bullet.h"

Bullet::Bullet(int startX, int startY, Direction dir, float bulletSpeed)
    : m_x(startX), m_y(startY), m_direction(dir), m_speed(bulletSpeed), m_active(true)
{
}

void Bullet::move() {
    switch (m_direction) {
    case Direction::UP:
        m_x -= 1;
        break;
    case Direction::DOWN:
        m_x += 1;
        break;
    case Direction::LEFT:
        m_y -= 1;
        break;
    case Direction::RIGHT:
        m_y += 1;
        break;
    }
}

void Bullet::deactivate() {
    m_active = false;
}

int Bullet::getX() const
{
    return m_x;
}
int Bullet::getY() const
{ 
    return m_y; 
}
Direction Bullet::getDirection() const {
    return m_direction;
}

bool Bullet::isActive() const { 
    return m_active; 
}
void Bullet::setX(int x)
{
    m_x = x;
}
void Bullet::setY(int y) { 
    m_y = y; 
}
void Bullet::setDirection(Direction direction) { 
    m_direction = direction; 
}
void Bullet::setSpeed(float speed) { 
    m_speed = speed; 
}
void Bullet::setActive(bool active) { 
    m_active = active; 
}
