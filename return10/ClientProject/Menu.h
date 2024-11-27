#pragma once

#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <crow.h>
class Menu {
public:
    int currentUserId=-1;
    virtual void display() = 0;
    void setCurrentUserId(int id);
    int getCurrentUserId();
};

