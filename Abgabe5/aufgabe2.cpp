#include <cassert>
#include <iostream>
#include <optional>

template <class T>
struct IsOptional {
    static constexpr bool value = false;
};

template <class T>
struct IsOptional<std::optional<T>> {
    static constexpr bool value = true;
};

template <class T>
inline constexpr bool IsOptionalV = IsOptional<T>::value;

int main() {
    assert(!IsOptionalV<int>);
    assert(IsOptionalV<std::optional<int>>);

    std::cout << "Exercise 2: all tests passed\n";
}
