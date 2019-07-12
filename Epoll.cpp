#include "Epoll.h"


void Epoll::EpollAdd(const int fd){
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLPRI | EPOLLRDHUP | EPOLLET;
	std::unique_lock<std::mutex> lock(mutex);
	if(epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd, &event) < 0){
		err("epoll_ctl add err");
	}
}

void Epoll::EpollMod(const int fd){
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLPRI | EPOLLRDHUP | EPOLLET;
	std::unique_lock<std::mutex> lock(mutex);
	if(epoll_ctl(epollfd_, EPOLL_CTL_MOD, fd, &event) <0){
		err("epoll_ctl mod err");
	}
}

void Epoll::EpollDel(const int fd){
	std::unique_lock<std::mutex> lock(mutex);
	if(epoll_ctl(epollfd_, EPOLL_CTL_DEL, fd, NULL) < 0){
		err("epoll_ctl del err");
	}
}

int Epoll::EpollWait(std::vector<struct epoll_event> &events){
	int ret;
	while(true){
		ret = epoll_wait(epollfd_, &*events.begin(), static_cast<int>(events.size()), 1000);
		if(ret < 0){
			if(errno == EINTR){
				continue;
			}
			else{
				//err("epoll wait err");
				return ret;
			}
		}
		if(ret == 0){
			continue;
		}
		if(ret == events.size()){
			events.resize(events.size()*2);
		}
		return ret;
	}
	return 0;
}
