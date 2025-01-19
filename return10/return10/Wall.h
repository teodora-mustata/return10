#pragma once
#include <memory>
#include "Bomb.h"

class Wall {
public:
    Wall(int x, int y, bool destructible);
    ~Wall() = default;

    Wall(const Wall& other);

    Wall& operator=(const Wall& other);

    Wall(Wall&& other) noexcept = default;
    Wall& operator=(Wall&& other) noexcept = default;

    int getX();
    int getY();
    bool isDestructible() const;
    void setContainedBomb(std::shared_ptr<Bomb> bomb);
    std::shared_ptr<Bomb> getContainedBomb() const;

private:
    int m_posX, m_posY;
    bool m_destructible;
    std::shared_ptr<Bomb> m_containedBomb;
};
