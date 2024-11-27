#pragma once

#include "Menu.h"

class Leaderboard : public Menu {
public:
    void display() override;
    void displayPlayersByCrowns();
};

