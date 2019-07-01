/*
 * @brief:对socket函数进行包裹
 */
#ifndef SOCKET_H
#define SOCKET_H
#include "Err.h"
#include <sys/socket.h>

int Socket(int family, int type, int protocol){
	int sockfd;
	if( (sockfd = socket(family, type, protocol)) < 0){
		err("socket error");
	}
	return sockfd;
}

int Bind(int sockfd, struct sockaddr * servaddr, size_t addr_len){
	int ret;
	if( (ret = bind(sockfd, servaddr, addr_len)) < 0){
		err("bind error");
	}
	return ret;
}

int Listen(int sockfd, int max_conn){
	int ret;
	if( (ret=listen(sockfd,max_conn)) < 0){
		err("listen error");
	}
	return ret;
}

int Accept(int sockfd, struct sockaddr * peer_addr, socklen_t* peer_len){
	int connfd;
	if( (connfd = accept(sockfd,peer_addr,peer_len)) < 0){
		err("accept error");
	}
	return connfd;
}
#endif
