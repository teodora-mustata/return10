export module validation; 
import <string_view>;      
import <string>;           
import <regex>;            

export class __declspec(dllexport) Validator {
public:
    static bool ValidatePassword(std::string_view password);
    static bool ValidateUserInput(std::string_view input);
};