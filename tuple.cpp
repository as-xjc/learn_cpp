#include <iostream>
#include <tuple>

std::tuple<int, int, bool> GetValue(int i) {
    if (i < 10) {
        return std::make_tuple(1, 2, true);
    } else {
        return std::make_tuple(3, 4, false);
    }
}

int main(int argc, char* argv[]) {
    int a;
    int b;
    bool result;
    std::tie(std::ignore, b, result) = GetValue(1);
    std::cout << "a:" << a << " b:" << b << " result:" << result << std::endl;

    // c++17
    auto [aa, bb , cc] = GetValue(20);
    std::cout << "a:" << aa << " b:" << bb << " result:" << cc << std::endl;

    return 0;
}

