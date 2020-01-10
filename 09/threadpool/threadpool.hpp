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
