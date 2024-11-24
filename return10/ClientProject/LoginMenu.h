#pragma once
#include <string>
#include <iostream>

class LoginMenu
{
public:
    void display();                   // Afișează meniul de login/sign up
    bool handleLogin(const std::string& username, const std::string& password); // Trimite datele către server pentru validare
    bool handleSignUp(const std::string& username, const std::string& password); // Trimite datele către server pentru crearea unui cont
    void showErrorMessage(const std::string& message); // Afișează mesaj de eroare dacă login/sign up eșuează
};

