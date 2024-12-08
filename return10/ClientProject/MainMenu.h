#pragma once
#include "Menu.h"
#include "ShopMenu.h"  
#include "Leaderboard.h"  
#include "GameInterface.h"
#include <chrono>
#include <thread>

class MainMenu : public Menu {
public:
    void display() override;  
};

