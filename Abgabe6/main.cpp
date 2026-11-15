#include <iostream>

#include "tuple.hpp"

int main() {
    Tuple<int, float, int> t(2, 1.2, 9);
    std::cout << t.get<0>() << "\n";
    std::cout << t.get<1>() << "\n";
    std::cout << t.get<2>() << "\n";
}
