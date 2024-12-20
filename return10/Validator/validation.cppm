export module validation;
import <string>;


export class __declspec(dllexport) Validator
{
public:
	bool ValidatePassword(const std::string& password);
	bool ValidateUserInput(const std::string& input);
};
