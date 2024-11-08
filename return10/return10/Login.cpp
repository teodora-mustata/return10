
#include "Login.h"

bool Login::loginUser(const std::string& username, const std::string& password)
{
    auto it = m_users.find(username);

    if (it != m_users.end() && it->second.GetPassword() == password) {
        m_loggedInUser = username;
        std::cout << "Login successful! Welcome, " << username << "!" << std::endl;
        return true;
    }
    else {
        std::cout << "Login failed: Invalid username or password." << std::endl;
        return false;
    }
}

bool Login::isLoggedIn() const
{
    return !m_loggedInUser.empty();
}

std::string Login::getLoggedInUser() const
{
    return m_loggedInUser;
}


void Login::displayUsers() const {
    std::cout << "Registered users:" << std::endl;
    for (const auto& user : m_users) {
        std::cout << "- " << user.first << std::endl;
    }
}

