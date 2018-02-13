#include <iostream>
#include <cstdio>
#include <set>
#include <thread>
#include <vector>

void static_or_local_lambda() {
  static auto generator = []() {
    return 1;
  };

  auto generator2 = []() {
    return 1;
  };

  std::printf("generator 1:%p\n", &generator);
  std::printf("generator 2:%p\n", &generator2);
}

void print_lambda_point() {
  static_or_local_lambda();
  static_or_local_lambda();

  std::thread test([]() {
    static_or_local_lambda();
    static_or_local_lambda();
  });

  test.join();
}

void find_if() {
  std::vector<int> vector{1,2,3,4,5,6,7,8,9,10};

  std::printf("\nvector:\n\t");
  for (auto& i : vector) {
    std::printf("%d ", i);
  }
  std::printf("\n");

  /**
   * param auto in lambda support start in C++14
   * in C++11:
   * @code
   *   auto it = std::find_if(std::begin(vector), vector.end(), [](const int& value) {
   *        return value == 5;
   *   });
   * @endcode
   */
  auto it = std::find_if(std::begin(vector), vector.end(), [](const auto& value) {
    return value == 5;
  });

  if (it == vector.end()) {
    std::cout << "find_if not found" << std::endl;
  } else {
    std::cout << "find_if ：" << *it << std::endl;
  }
}

int main() {
  print_lambda_point();
  find_if();

  return 0;
}