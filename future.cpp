#include <future>
#include <thread>
#include <map>
#include <functional>
#include <iostream>

std::map<int, std::function<bool()>> handlers;
static int index_ = 0;

template <typename RETURN>
void async_run(std::function<RETURN()>&& call, std::function<void(RETURN)>&& cb) {
  auto f = std::async(std::launch::async, std::move(call));
  auto fu = std::make_shared<std::future<RETURN>>(std::move(f));
  auto callcb = std::make_shared<std::function<void(RETURN)>>(std::move(cb));
  auto check = [callcb, fu]() -> bool {
    if (fu->wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
      (*callcb)(fu->get());
      return true;
    }
    return false;
  };

  handlers.emplace(index_++, std::move(check));
};

template <typename RETURN>
void async_run(RETURN(*call)(), void(*cb)(RETURN)) {
  async_run(std::function<RETURN()>(call), std::function<void(RETURN)>(cb));
}

template <typename RETURN>
void async_run(std::function<RETURN()>&& call, void(*cb)(RETURN)) {
  async_run(std::move(call), std::function<void(RETURN)>(cb));
}

template <typename RETURN>
void async_run(RETURN(*call)(), std::function<void(RETURN)>&& cb) {
  async_run(std::function<RETURN()>(call), std::move(cb));
}


int call() {
  std::cout << std::time(nullptr) << " start sleep" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(10));
  std::cout << std::time(nullptr) << " end sleep" << std::endl;
  return 5;
}

void callcb(int i) {
  std::cout << std::time(nullptr) << " callback:" << i << std::endl;
}

int main() {
  async_run(call, callcb);
  async_run(call, std::function<void(int)>([](int i) {
    std::cout << std::time(nullptr) << " callback:" << i << std::endl;
  }));
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