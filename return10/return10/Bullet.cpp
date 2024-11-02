#include "Bullet.h"
Bullet::Bullet(int startX, int startY, Direction dir, float speed)
    : x(startX), y(startY), direction(dir), speed(speed), active(true),
    fired_at(std::chrono::steady_clock::now())
{
}


bool Bullet::checkPlayerCollision(Player& target) {
     int targetX = target.GetPosition().first;
     int targetY = target.GetPosition().second;

     if (x == targetX && y == targetY) {
        target.resetPosition(); 
        deactivate(); 
        target.loseLife();
        return true; 
     }
     return false; 
}


bool Bullet::checkWallCollision(Map& map) {
    CellType cell = map.get_cell_type(x, y);

        
    if (auto* wall = std::get_if<Wall>(&cell)) {
        if (wall->is_destructible()) {
                map.set_cell_type(x, y, std::monostate{}); 
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
    auto offset = DirectionUtils::toOffset(direction);
    x += static_cast<int>(offset.first * speed);
    y += static_cast<int>(offset.second * speed);
}


void Bullet::deactivate() {
    active = false; 
}
