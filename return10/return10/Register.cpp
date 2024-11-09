#include "Register.h"

bool Register::registerUser(const std::string& username, const std::string& password)
{
    if (userExists(username)) {
        std::cout << "Registration failed: Username already exists." << std::endl;
        return false;
    }

    if (!isPasswordValid(password)) {
        std::cout << "Registration failed: Password does not meet security requirements." << std::endl;
        return false;
    }

    PlayerDAO newPlayer(username, password);

    m_users[username] = newPlayer;

    std::cout << "Registration successful! Player " << username << " has been created and saved in the database." << std::endl;
    return true;
}

bool Register::userExists(const std::string& username) const
{
    return m_users.find(username) != m_users.end();
}

const PlayerDAO* Register::getPlayer(const std::string& username) const
{
    auto it = m_users.find(username);
    if (it != m_users.end()) {
        return &(it->second);
    }
    return nullptr;
}

bool Register::isPasswordValid(const std::string& password)
{
    const std::regex passwordPattern("^(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9])(?=.*[aeiouAEIOU])(?=.*[!@#$%^&*]).{8,}$");
    return std::regex_match(password, passwordPattern);
}

