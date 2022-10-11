#include "ThreadPoolI.h"

ThreadPoolI::ThreadPoolI(uint32_t num_threads) {
    threads.reserve(num_threads);
    for (uint32_t i = 0; i < num_threads; ++i) {
        threads.emplace_back(&ThreadPoolI::run, this);
    }
}

void ThreadPoolI::run() {
    while (!quite) {
        std::unique_lock<std::mutex> lock(q_mtx);

        q_cv.wait(lock, [this]()->bool { return !q.empty() || quite; });

        if (!q.empty()) {
            auto elem = std::move(q.front());
            q.pop();
            lock.unlock();

            elem.first.get();

            std::lock_guard<std::mutex> lock(completed_task_ids_mtx);

            completed_task_ids.insert(elem.second);

            completed_task_ids_cv.notify_all();
        }
    }
}

void ThreadPoolI::wait(int64_t task_id) {
    std::unique_lock<std::mutex> lock(completed_task_ids_mtx);

    completed_task_ids_cv.wait(lock, [this, task_id]()->bool {
        return completed_task_ids.find(task_id) != completed_task_ids.end();
    });
}
void ThreadPoolI::wait_all() {
    std::unique_lock<std::mutex> lock(q_mtx);

    completed_task_ids_cv.wait(lock, [this]()->bool {
        std::lock_guard<std::mutex> task_lock(completed_task_ids_mtx);
        return q.empty() && last_idx == completed_task_ids.size();
    });
}
bool ThreadPoolI::calculated(int64_t task_id) {
    std::lock_guard<std::mutex> lock(completed_task_ids_mtx);
    if (completed_task_ids.find(task_id) != completed_task_ids.end()) {
        return true;
    }
    return false;
}
ThreadPoolI::~ThreadPoolI() {
    quite = true;
    for (uint32_t i = 0; i < threads.size(); ++i) {
        q_cv.notify_all();
        threads[i].join();
    }
}