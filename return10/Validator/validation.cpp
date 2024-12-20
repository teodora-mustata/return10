module validation;

import <regex>;

bool Validator::ValidatePassword(const std::string& password)
{
    std::regex passwordRegex("^(?=.*[A-Z])(?=.*[0-9])(?=.*!@#$%^&*).{8,}$");
    return std::regex_match(password, passwordRegex);
}

bool Validator::ValidateUserInput(const std::string& input)
{
    std::regex inputRegex("^[w|a|s|d|f]{1}$");
    return std::regex_match(input, inputRegex);
}
