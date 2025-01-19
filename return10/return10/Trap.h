#pragma once

#include <utility> 
#include "Player.h"
class Trap {
public:
    Trap(int x, int y);
    virtual ~Trap() = default;

    std::pair<int, int> GetCoordinates() const;
    bool IsActive() const;
    void SetState(bool isActive);

    virtual void activateEffect(Player& player) = 0;

protected:
    std::pair<int, int> m_coordinates;
    bool m_isActive = true;
};
