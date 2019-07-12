/*
 * @brief:对socket函数进行包裹
 */
#ifndef SOCKET_H
#define SOCKET_H
#include "Err.h"
#include "fcntl.h"
#include <sys/socket.h>



int Socket(int family, int type, int protocol);
int Bind(int sockfd, struct sockaddr * servaddr, size_t addr_len);
int Listen(int sockfd, int max_conn);
int Accept(int sockfd, struct sockaddr * peer_addr, socklen_t* peer_len);
int SetSocketNonBlocking(const int fd);
#endif
