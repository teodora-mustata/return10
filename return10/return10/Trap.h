#pragma once

#include <utility> 
#include "Player.h"
class Trap {
public:
    Trap(int x, int y);
    virtual ~Trap() = default;

    std::pair<int, int> getCoordinates() const;
    bool isActive() const;
    void setState(bool isActive);

    virtual void activateEffect(Player& player) = 0;

protected:
    std::pair<int, int> m_coordinates;
    bool m_isActive = true;
};
