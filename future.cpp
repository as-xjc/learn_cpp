#include <future>
#include <thread>
#include <map>
#include <functional>
#include <iostream>

using handler = std::function<bool()>;

std::map<int, handler> handlers;
static int index_ = 0;

template <typename RETURN, typename... ARGS>
void async_run(std::function<RETURN(ARGS...)> call, std::function<void(RETURN)> cb) {
  auto f = std::async(std::launch::async, call);
  auto fu = new std::future<RETURN>(std::move(f));
  auto check = [&call, cb, fu]() -> bool {
    if (fu->wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
      cb(fu->get());
      delete fu;
      return true;
    }
    return false;
  };

  handlers.emplace(index_++, std::move(check));
};


int call() {
  std::cout << std::time(nullptr) << " start sleep" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(5));
  std::cout << std::time(nullptr) << " end sleep" << std::endl;
  return 5;
}

void callcb(int i) {
  std::cout << std::time(nullptr) << " callback:" << 1 << std::endl;
}

int main() {

  async_run(std::function<int(void)>(call), std::function<void(int)>(callcb));
  std::this_thread::sleep_for(std::chrono::seconds(1));
  while (true) {
    std::cout <<std::time(nullptr) <<  " run a loop" << std::endl;
    for (auto it = handlers.begin(); it != handlers.end(); ) {
      std::cout <<std::time(nullptr) <<  " checking " << it->first << std::endl;
      if ((it->second)()) {
        it = handlers.erase(it);
      } else {
        ++it;
      }
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
  return 0;
}