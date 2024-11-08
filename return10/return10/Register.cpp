#include "Register.h"



bool Register::userExists(const std::string& username) const
{
    return m_users.find(username) != m_users.end();
}


bool Register::isPasswordValid(const std::string& password)
{
    const std::regex passwordPattern("^(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9])(?=.*[aeiouAEIOU])(?=.*[!@#$%^&*]).{8,}$");
    return std::regex_match(password, passwordPattern);
}


