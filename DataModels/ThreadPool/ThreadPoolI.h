#pragma once
#include <queue>
#include <condition_variable>
#include <unordered_set>
#include <atomic>
#include <mutex>
#include <thread>
#include <future>
#include <Windows.h>

class ThreadPoolI
{
	std::queue<std::pair<std::future<void>, int64_t>> q;
	
	std::mutex q_mtx;
	std::condition_variable q_cv;

	std::unordered_set<int64_t> completed_task_ids;

	std::condition_variable completed_task_ids_cv;
	std::mutex completed_task_ids_mtx;

	std::vector<std::thread> threads;

	std::atomic<bool> quite{ false };

	std::atomic<int64_t> last_idx{0};

public:
    ThreadPoolI(uint32_t num_threads = 2);
	void run();
    template <typename Func, typename ...Args>
    int64_t add_task(const Func& task_func, Args&&... args) {
        int64_t task_idx = last_idx++;

        std::lock_guard<std::mutex> q_lock(q_mtx);
        q.emplace(std::async(std::launch::deferred, task_func, args...), task_idx);

        q_cv.notify_one();
        return task_idx;
    }

	void wait(int64_t task_id);

	void wait_all();
	bool calculated(int64_t task_id);
	~ThreadPoolI();
};

