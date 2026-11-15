#pragma once

#include <cstddef>

template <typename T, typename... Rest>
class Tuple {
public:
    Tuple(T v, Rest... r) : value(v), rest(r...) {}

    template <std::size_t idx>
    auto get() const {
        if constexpr (idx == 0) {
            return value;
        } else {
            return rest.template get<idx - 1>();
        }
    }

private:
    T value;
    Tuple<Rest...> rest;
};

template <typename T>
class Tuple<T> {
public:
    Tuple(T v) : value(v) {}

    template <std::size_t idx>
    auto get() const {
        static_assert(idx == 0, "index out of range");
        return value;
    }

private:
    T value;
};
