#include "vector.hpp"

#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

int main() {
    Vector<float> floats;
    assert(floats.empty());
    for (int i = 0; i < 100; ++i) {
        floats.push_back(i * 0.5f);
    }
    assert(floats.size() == 100);
    assert(floats.capacity() >= 100);
    assert(floats[99] == 49.5f);

    Vector<std::string> strings{"Hello", "World"};
    strings.push_back("!");
    assert(strings.size() == 3);
    assert(strings.front() == "Hello");
    assert(strings.back() == "!");

    Vector<int> filled(3, 7);
    assert(filled.size() == 3 && filled[0] == 7 && filled[2] == 7);

    Vector deduced{1, 2, 3};
    static_assert(std::is_same_v<decltype(deduced), Vector<int>>);

    Vector<std::string> copy = strings;
    copy[0] = "Goodbye";
    assert(strings[0] == "Hello");
    assert(copy[0] == "Goodbye");

    const std::string* buffer = copy.data();
    Vector<std::string> moved = std::move(copy);
    assert(moved.data() == buffer);
    assert(copy.empty() && copy.data() == nullptr);

    Vector<std::string> assigned;
    assigned = strings;
    assert(assigned.size() == strings.size() && assigned[1] == "World");
    assigned = std::move(moved);
    assert(assigned[0] == "Goodbye");

    Vector<std::string> self{"x"};
    assert(self.size() == self.capacity());
    self.push_back(self[0]);
    assert(self[1] == "x");

    Vector<std::unique_ptr<int>> pointers;
    for (int i = 0; i < 10; ++i) {
        pointers.push_back(std::make_unique<int>(i));
    }
    assert(*pointers[9] == 9);

    bool thrown = false;
    try {
        filled.at(3);
    } catch (const std::out_of_range&) {
        thrown = true;
    }
    assert(thrown);

    filled.pop_back();
    assert(filled.size() == 2);
    filled.clear();
    assert(filled.empty());

    int sum = 0;
    for (int value : deduced) {
        sum += value;
    }
    assert(sum == 6);

    std::cout << "Exercise 1: all tests passed\n";
}
