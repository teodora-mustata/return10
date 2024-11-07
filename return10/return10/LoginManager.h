#pragma once
#include <string>
#include <unordered_set>
#include <iostream>

class LoginManager {
private:
    std::unordered_set<std::string> userDatabase;
public:
    LoginManager();
    bool loginUser(const std::string& username);
    void displayUsers() const;
};


