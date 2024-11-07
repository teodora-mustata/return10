#include "Login.h"
//more of a mock implementation to simply place in the GameInterface, obviously needs the whole SQL implementation
LoginManager::LoginManager() {
    // here would load the database
}

bool LoginManager::loginUser(const std::string& username)
{
    if (userDatabase.find(username) != userDatabase.end()) 
    {
        std::cout << "Welcome, " << username <<  std::endl;
        return false;  // username exists and enter
    }
    else
    {
        userDatabase.insert(username);
        std::cout << "Welcome, " << username << "you are now a new player." << std::endl;
        return true;
    }
}

void LoginManager::displayUsers() const {
    std::cout << "Registered users:" << std::endl;
    for (const auto& user : userDatabase) {
        std::cout << "- " << user << std::endl;
    }
}
