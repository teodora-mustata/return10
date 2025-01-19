module validation;

import <regex>;

// Implementarea func?iilor
bool Validator::ValidatePassword(std::string_view password) {
    std::regex passwordRegex(R"(^(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#$%^&*]).{8,}$)");
    // Conversie explicit? la std::string pentru regex_match
    std::string sPassword = std::string(password);
    return std::regex_match(sPassword, passwordRegex);
}

bool Validator::ValidateUserInput(std::string_view input) {
    std::regex inputRegex(R"(^[W|A|S|D|F]{1}$)");
    // Conversie explicit? la std::string pentru regex_match
    return std::regex_match(std::string(input), inputRegex);
}

