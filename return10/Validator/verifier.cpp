module verification;

template <typename T>
bool IsEmpty(const T& value)
{
    if constexpr (std::is_same_v<T, std::string>) {
        return value.empty();
    } else if constexpr (std::is_integral_v<T>) {
        return value == 0;
    } else if constexpr (std::is_pointer_v<T>) {
        return value == nullptr;
    } else {
        return false;  
    }
}

template <typename... Args>
bool Verifier::AreEmpty(Args&&... args)
{
    return (IsEmpty(std::forward<Args>(args)) && ...);
}