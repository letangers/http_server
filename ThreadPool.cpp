#include "ThreadPool.h"

void ThreadFunc(ThreadPool * tp){
	while(!tp->stop_.load()){
		task_t task;
		//Put the acquisition task in a separate scope
		{
			std::unique_lock<std::mutex> lock(tp->mutex);
			tp->not_empty.wait(lock,[tp]{
					return tp->stop_.load() || !tp->tasks_.empty() ;
			});
			if(tp->stop_ && tp->tasks_.empty()){
				return;
			}
			task = std::move(tp->tasks_.front());
			tp->tasks_.pop();
		}
		tp->idle_thread_num_--;
		//if reture turn,keep-alive is true.
		//exec epoll_mod
		if(task->handle() == 1){
			tp->epoll_->EpollMod(task->GetConnfd());
		}
		tp->idle_thread_num_++;
	}
}

void push_task(ThreadPool * tp){
	int ret;
	std::vector<struct epoll_event> events(16);
	while(!tp->stop_.load()){
		ret = tp->epoll_->EpollWait(events);
		if(ret <= 0){
			//deal error
			continue;
		}
		for(int i = 0;i < ret;i++){
			std::unique_lock<std::mutex> lock(tp->mutex);
			para_t para =std::make_shared<struct epoll_event>(events[i]);
			tp->tasks_.emplace(std::make_shared<Handle>(para));
			tp->not_empty.notify_one();
			//if don't need para in ThreadFunc,use below line
			//tasks_.push(std::bind(ThreadFunc,para));
		}
	}
}


//ThreadPool::ThreadPool(std::shared_ptr<Epoll> epoll, int thread_num):stop_(false){
ThreadPool::ThreadPool(int thread_num):stop_(false){
	epoll_ = std::make_shared<Epoll>();
	if(thread_num < 1){
		thread_num = 1;
	}
	idle_thread_num_.store(thread_num);
	for(int i = 0;i < thread_num; i++){
		pool_.emplace_back(std::thread(ThreadFunc,this));
		//pool_.push_back(std::thread(ThreadFunc));
	}
}

ThreadPool::~ThreadPool(){
	stop_.store(true);
	add_task_.join();
	not_empty.notify_all();
	for(std::thread &one : pool_){
		one.join();
	}
}


bool ThreadPool::start(){
	add_task_ = std::move(std::thread(push_task,this));
	return true;
}
