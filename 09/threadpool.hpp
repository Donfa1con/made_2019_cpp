#pragma once

#include <future>
#include <vector>
#include <queue>


class ThreadPool {
  public:
    using QueueTask = std::function<void()>;

    explicit ThreadPool(size_t pool_size);
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;
    ~ThreadPool();

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;

  private:
    bool keep_working;
    size_t pool_size_;
    std::mutex mutex_;
    std::queue<QueueTask> queue_;
    std::vector<std::thread> threads_;
    std::condition_variable notifier;
};

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

template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
    using Task = std::packaged_task<decltype(func(args...))()>;
    
    auto task = new Task(std::bind(func, args...));
    auto future = task->get_future();
    {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push([task]() {
            (*task)();
            delete task;
        });
    }
    notifier.notify_all();
    return future;
}

ThreadPool::~ThreadPool() {
    keep_working = false;
    notifier.notify_all();
    for (auto& thread: threads_) {
        thread.join();
    }
}
