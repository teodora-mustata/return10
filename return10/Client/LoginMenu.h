#pragma once
//#include <string>
//#include <iostream>
//#include <cpr/cpr.h>
//#include <crow.h>
#include "Menu.h"
#include <regex>
//import validation;
class LoginMenu :public Menu
{
public:
    void display();                   // Afișează meniul de login/sign up
    bool passwordValidation(const std::string& password);
    bool handleLogin(const std::string& username, const std::string& password); // Trimite datele către server pentru validare
    bool handleSignUp(const std::string& username, const std::string& password); // Trimite datele către server pentru crearea unui cont
    void showErrorMessage(const std::string& message); // Afișează mesaj de eroare dacă login/sign up eșuează
};

