export module verification;
import <string>;
import <type_traits>;

export class __declspec(dllexport) Verifier
{
public:
    template <typename... Args>
    bool AreEmpty(Args&&... args);
};