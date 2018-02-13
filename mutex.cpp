#include <iostream>
#include <shared_mutex>
#include <mutex>

void lock_multi_mutex() {
  std::mutex m1, m2, m3;

  /**
   * in C++17, can do as
   * @code
   *    std::scoped_lock l(m1, m2, m3);
   * @endcode
   */
  {
    std::lock(m1, m2, m3);

    // unlock by RAII
    std::lock_guard<std::mutex> lg1(m1, std::adopt_lock);
    std::lock_guard<std::mutex> lg2(m2, std::adopt_lock);
    std::lock_guard<std::mutex> lg3(m3, std::adopt_lock);
  }
}

void test_rw() {
  /**
   * shared_mutex in C++17
   */
  std::shared_mutex mutex;
  std::shared_lock<std::shared_mutex> lock1(mutex);
  std::cout << "read 1" << std::endl;
  std::shared_lock<std::shared_mutex> lock2(mutex);
  std::cout << "read 2" << std::endl;
  lock1.unlock();
  lock2.unlock();
  std::unique_lock<std::shared_mutex> lock3(mutex);
  std::cout << "write 1" << std::endl;
}

int main() {
  test_rw();
  lock_multi_mutex();

  return 0;
}
