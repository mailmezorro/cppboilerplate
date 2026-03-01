#include <iostream>
#include "mylib/mylib.hpp"

int main() {
    const int a = 3;
    const int b = 4;

    std::cout << "mylib::add(" << a << ", " << b << ") = "
              << mylib::add(a, b) << "\n";
    std::cout << "mylib::multiply(" << a << ", " << b << ") = "
              << mylib::multiply(a, b) << "\n";

    return 0;
}
