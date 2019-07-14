#include "Socket.h"

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
		//err("accept error");
	}
	return connfd;
}

int SetSocketNonBlocking(const int fd){
    int flag = fcntl(fd, F_GETFL, 0);
    if(flag == -1){
        return -1;
	}
    flag |= O_NONBLOCK;
    if(fcntl(fd, F_SETFL, flag) == -1){
        return -1;
	}
    return 0;
}
