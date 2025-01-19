export module validation;
import <string>;


export class __declspec(dllexport) Validator
{
public:
	bool validatePassword(const std::string& password);
	bool validateUserInput(const char& input);
};