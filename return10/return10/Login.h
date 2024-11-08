
#pragma once
#include <string>
#include <iostream>
#include <unordered_map>//temporar
#include <regex>
#include "PlayerDAO.h"

class Login
{
public:
    Login() : m_loggedInUser("") {
        //temporar
        PlayerDAO d{ "nume","pakwnnw!AOan1" };
        m_users["player1"] = d;
    }

    //bool authenticate(const std::string& username, const std::string& password);

    bool loginUser(const std::string& username, const std::string& password);

    bool isLoggedIn() const;
    std::string getLoggedInUser() const;
    void displayUsers() const;
private:
    std::string m_loggedInUser;
    //bool checkCredentials(const std::string& username, const std::string& password);

    //temporar
    std::unordered_map<std::string, PlayerDAO> m_users;
};





