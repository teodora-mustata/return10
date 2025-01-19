#include "Wall.h"


Wall::Wall(int x, int y, bool destructible)
    : m_posX(x), m_posY(y), m_destructible(destructible), m_containedBomb(nullptr) {}


Wall::Wall(const Wall& other)
    : m_posX(other.m_posX), m_posY(other.m_posY), m_destructible(other.m_destructible) {
    if (other.m_containedBomb) {
        m_containedBomb = std::make_unique<Bomb>(*other.m_containedBomb);
    }
}

Wall& Wall::operator=(const Wall& other) {
    if (this != &other) {
        m_posX = other.m_posX;
        m_posY = other.m_posY;
        m_destructible = other.m_destructible;
        if (other.m_containedBomb) {
            m_containedBomb = std::make_unique<Bomb>(*other.m_containedBomb); 
        }
        else {
            m_containedBomb.reset();
        }
    }
    return *this;
}


int Wall::getX() { return m_posX; }

int Wall::getY() { return m_posY; }

bool Wall::isDestructible() const { return m_destructible; }

void Wall::setContainedBomb(std::shared_ptr<Bomb> bomb) {
    m_containedBomb = std::move(bomb);
}

std::shared_ptr<Bomb> Wall::getContainedBomb() const { return m_containedBomb; }
