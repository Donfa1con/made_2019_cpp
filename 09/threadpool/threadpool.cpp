#include "threadpool.hpp"


ThreadPool::ThreadPool(size_t pool_size)
: keep_working(true), pool_size_(pool_size), threads_(pool_size) {
    for (size_t i = 0; i < pool_size_; ++i) {
        threads_[i] = std::thread([this](){
            while (keep_working) {
                std::unique_lock<std::mutex> lock(mutex_);
                notifier.wait(lock, [this]() {
                    return !queue_.empty() || !keep_working;
                });
                if (queue_.empty()) {
                    return;
                }
                auto task = queue_.front(); queue_.pop();
                lock.unlock();
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    keep_working = false;
    notifier.notify_all();
    for (auto& thread: threads_) {
        thread.join();
    }
}
