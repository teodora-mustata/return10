#pragma once
#include "Menu.h"
#include <regex>
//import validation;
class LoginMenu:public Menu
{
public:
    void display();
    bool passwordValidation(const std::string& password);
    bool handleLogin(const std::string& username, const std::string& password);
    bool handleSignUp(const std::string& username, const std::string& password);
    void showErrorMessage(const std::string& message);
};

