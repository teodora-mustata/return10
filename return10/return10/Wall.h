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
    void setContainedBomb(std::unique_ptr<Bomb> bomb);
    Bomb* getContainedBomb() const;

private:
    int m_posX, m_posY;
    bool m_destructible;
    std::unique_ptr<Bomb> m_containedBomb;
};
