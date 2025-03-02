#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

#include "ThreadPool/ThreadPool.hpp"

auto main() -> int
{
  progschj::ThreadPool pool(4);
  std::vector<std::future<int> > results;

  for (int i = 0; i < 8; ++i) {
    results.emplace_back(pool.enqueue(
        [i]
        {
          std::cout << "hello " << i << std::endl;
          std::this_thread::sleep_for(std::chrono::seconds(1));
          std::cout << "world " << i << std::endl;
          return i * i;
        }));
  }

  pool.wait_until_empty();
  pool.wait_until_nothing_in_flight();

  for (auto&& result : results)
    std::cout << result.get() << ' ';
  std::cout << std::endl;

  return 0;
}
