#include "Bullet.h"
Bullet::Bullet(int startX, int startY, Direction dir, float speed)
    : x(startX), y(startY), direction(dir), speed(speed), active(true),
    fired_at(std::chrono::steady_clock::now())
{
}

void Bullet::move() {
    auto offset = DirectionUtils::toOffset(direction);
    x += static_cast<int>(offset.first * speed);
    y += static_cast<int>(offset.second * speed);
}


void Bullet::deactivate() {
    active = false; 
}
