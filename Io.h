#ifndef IO_H
#define IO_H

#include <unistd.h>
#include <errno.h>
#include "Err.h"

ssize_t Read(int fd,void *buff, size_t nbytes);
ssize_t Write(int fd,const void *buff, size_t nbytes);

ssize_t readn(int fd, void * buff, size_t nbytes);
ssize_t writen(int fd, const void * buff, size_t nbytes);
ssize_t readline(int fd, void * buff, size_t nbytes);

ssize_t Close(int fd);


#endif
