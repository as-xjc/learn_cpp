#include <iostream>

struct One {
  One () {
    std::cout << "this is One" << std::endl;
  }
  One(const One& other) {
    std::cout << "this is copy cot" << std::endl;
  }
  One(One&& other) {
    std::cout << "this is move cot" << std::endl;
  }
  One& operator=(One&& other) {
    std::cout << "this is move=" << std::endl;
    return *this;
  }
  One& operator=(const One& other) {
    std::cout << "this is copy=" << std::endl;
    return *this;
  }
};

void test(One&& other) {
  One e(other);
  One ee(std::move(other));
}

int main() {
  One e;
  test(std::move(e));
  return 0;
}