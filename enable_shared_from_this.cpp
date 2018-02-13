#include <iostream>
#include <memory>

class Test1 {
 public:
  virtual void print() {
    std::cout << "test1" << std::endl;
  }
};

class Test2 : public Test1, public std::enable_shared_from_this<Test2> {
 public:
  void print() override {
    std::cout << "test2" << std::endl;
  }
};

int main() {
  auto test1 = std::make_shared<Test1>();
  auto test2 = std::make_shared<Test2>();

  test1->print();

  auto test11 = std::dynamic_pointer_cast<Test1>(test2);
  if (test11) {
    std::cout << "std::dynamic_pointer_cast<Test1>(test2) :";
    test11->print();
  } else {
    std::cout << "std::dynamic_pointer_cast<Test1>(test2) fail" << std::endl;
  }

  auto test22 = test2->shared_from_this();
  test22->print();

  return 0;
}