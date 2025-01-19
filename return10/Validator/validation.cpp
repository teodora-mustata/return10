module validation;

import <regex>;

bool Validator::validatePassword(const std::string& password)
{
    std::regex passwordRegex(R"(^(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#$%^&*]).{8,}$)");
    return std::regex_match(password, passwordRegex);
}

bool Validator::validateUserInput(const char& input) {
    std::string inputStr(1, input); 
    std::regex inputRegex(R"(^[W|A|S|D|F]{1}$)");
    return std::regex_match(inputStr, inputRegex);
}
