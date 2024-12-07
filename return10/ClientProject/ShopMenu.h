#pragma once

#include "Menu.h"

class ShopMenu : public Menu {
public:
    void display() override;
    void buyReloadSpeedUpgrade();
    void buyBulletSpeedUpgrade();
};

