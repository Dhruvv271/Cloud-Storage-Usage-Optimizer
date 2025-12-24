#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
    std::queue<T> q;
    std::mutex m;
    std::condition_variable cv;
    bool closed = false;

public:
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(m);
        if (closed) return;
        q.push(value);
        cv.notify_one();
    }

    bool pop(T& out) {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [&]{ return closed || !q.empty(); });

        if (q.empty() && closed) return false;

        out = q.front();
        q.pop();
        return true;
    }

    void close() {
        std::lock_guard<std::mutex> lock(m);
        closed = true;
        cv.notify_all();
    }
};
