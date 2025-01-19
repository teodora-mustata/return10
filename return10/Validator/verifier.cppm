export module verifier;
import <string>;
import <type_traits>;

export class __declspec(dllexport) Verifier {
public:
    template <typename T>
    static bool isEmpty(const T& value) {
        if constexpr (std::is_same_v<T, std::string>) {
            return value.empty();
        }
        else if constexpr (std::is_integral_v<T>) {
            return value == 0;
        }
        else if constexpr (std::is_pointer_v<T>) {
            return value == nullptr;
        }
        else {
            return false;
        }
    }

    template <typename... Args>
    bool areEmpty(Args&&... args) {
        return (isEmpty(std::forward<Args>(args)) && ...);
    }
};
