#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

#include "Epoll.h"
#include "Handle.h"

using para_t = std::shared_ptr<struct epoll_event>;
using task_t = std::shared_ptr<Handle>;
class ThreadPool;
void ThreadFunc(ThreadPool *tp);
void push_task(ThreadPool * tp);


/*Temporarily set a fixed number of threads
 * todo:
 *		set a maximum number of threads,
 *		allow to add temporary threads,
 *		but the number of threads can't be larger than maximum, 
 *		and per temporary thread need to set a timeout for destory.
 */
class ThreadPool{
	public:
		/*
		int core_thread_num_;
		int max_thread_num_;
		*/
		std::atomic<bool> stop_;
		//thread pool
		std::vector<std::thread> pool_;
		//a thread to push task
		std::thread add_task_;

		/*
		using task_t = std::function<bool(para_t)>;
		std::queue<para_t> paras_;
		*/

		std::queue<task_t> tasks_;

		std::atomic<int> idle_thread_num_;

		std::mutex mutex;
		std::condition_variable not_empty;

		std::shared_ptr<Epoll> epoll_;

	public:
		//ThreadPool(std::shared_ptr<Epoll> epoll, int thread_num);
		ThreadPool(int thread_num);
		~ThreadPool();

		bool start();
};

#endif
