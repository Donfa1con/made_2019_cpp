#include <cassert>
#include <iostream>
#include <vector>

#include "threadpool/threadpool.hpp"


int main() {
    ThreadPool pool(2);
    std::vector<int> vec;
    auto fill_vec = [&vec]() {
        for (int i = 0; i < 100; ++i) {
            vec.push_back(i);
        }
        std::this_thread::sleep_for (std::chrono::milliseconds(100));
    };
    auto task1 = pool.exec(fill_vec);
    auto task2 = pool.exec([]() {
        std::this_thread::sleep_for (std::chrono::milliseconds(100));
        return 1;
    });
    auto task3 = pool.exec([](int a) {
        std::this_thread::sleep_for (std::chrono::milliseconds(100));
        return a;
    }, 100);

    task1.get();
    auto res2 = task2.get();
    auto res3 = task3.get();
    
    for (int i = 0; i < 100; ++i) {
        assert(vec[i] == i);
    }
    assert(res2 == 1);
    assert(res3 == 100);
    std::cout << "Tests passed!" << std::endl;
    return 0;
}
