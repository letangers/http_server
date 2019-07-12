#ifndef EPOLL_H
#define EPOLL_H

#include <sys/epoll.h>
#include <sys/errno.h>
#include <unistd.h>
#include <vector>
#include <mutex>

#include "Err.h"

class Epoll{
	private:
		int epollfd_;
		std::mutex mutex;
	public:
		Epoll():epollfd_(epoll_create1(EPOLL_CLOEXEC)){}
		~Epoll(){ close(epollfd_); }
		int GetEpollfd(){ return epollfd_; }
		void EpollAdd(const int fd);
		void EpollMod(const int fd);
		void EpollDel(const int fd);
		int EpollWait(std::vector<struct epoll_event> &events);
};

#endif
