#ifndef SERVER_H
#define SERVER_H

#include "Socket.h"
#include "Io.h"
#include "ThreadPool.h"
#include "Epoll.h"
#include <atomic>

//bzero
#include <strings.h>
#include <cstring>

//sockaddr_in 头文件
#include <netinet/in.h>

//htons
#include <arpa/inet.h>

//read write
#include <unistd.h>

#include "PerConnect.h"

#include <thread>

#include <poll.h>
#include <sys/epoll.h>

#include "data/static_data.h"

class Server;
void AcceptFunc(Server *sp);

class Server{
	public:
		Server(int thread_num, int port);
		~Server();

		void start();
	//private:
		int listenfd_;
		std::atomic<bool> start_;
		int port_;

		static const int MAXFD = 100000;

		std::unique_ptr<ThreadPool> thread_pool_;
		//std::shared_ptr<Epoll> epoll_;
		Epoll *epoll_;
		std::thread accept_thread_;

		bool Init();
};
#endif
