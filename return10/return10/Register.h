#pragma once
#include <string>
#include <unordered_map>
#include <regex>
#include <iostream>
#include "PlayerDAO.h"

class Register {
public:
    Register() {}

    bool registerUser(const std::string& username, const std::string& password);

    bool userExists(const std::string& username) const;

    const PlayerDAO* getPlayer(const std::string& username) const;
private:
    bool isPasswordValid(const std::string& password);
public:
    std::unordered_map<std::string, PlayerDAO> m_users;
};

