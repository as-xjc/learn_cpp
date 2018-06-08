#include <iostream>

template <typename T>
struct Singleton {
  Singleton() = delete;
  ~Singleton() = delete;

  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

  Singleton(Singleton&&) = delete;
  Singleton& operator=(Singleton&&) = delete;

  template <typename... ARGS>
  static T* Instance(ARGS&&... args) {
    static std::once_flag G_O;
    static T* G_T = nullptr;
    std::call_once(G_O, [&]() { G_T = new T(std::forward<ARGS>(args)...); });
    return G_T;
  }
};

int main(int argc, char* argv[]) {
  std::cout << Singleton<int>::Instance(1) << std::endl;
  auto i = Singleton<int>::Instance();
  std::cout << *Singleton<int>::Instance() << std::endl;
  std::cout << Singleton<int>::Instance(1) << std::endl;
  std::cout << Singleton<int>::Instance(2) << std::endl;
  std::cout << Singleton<int>::Instance() << std::endl;
  std::cout << Singleton<long>::Instance() << std::endl;

  return 0;
}