#include "Io.h"

ssize_t Read(int fd, void * buff, size_t nbytes){
	ssize_t ret;
	while( (ret = read(fd, buff, nbytes)) < 0){
		if(errno == EINTR){
			continue;
		}
		else{
			return -1;
		}
	}
	return ret;
}

ssize_t Write(int fd, const void * buff, size_t nbytes){
	ssize_t ret;
	while( (ret = write(fd, buff, nbytes)) < 0){
		if(errno == EINTR){
			continue;
		}
		else{
			return -1;
		}
	}
	return ret;
}

ssize_t readn(int fd, void * buff, size_t nbytes){
	size_t nleft=nbytes;
	ssize_t nread = 0;
	char *ptr = static_cast<char *>(buff);

	while(nleft>0){
		if( (nread = read(fd, ptr, nleft)) < 0){
			if(errno == EINTR){
				nread = 0;
			}
			else{
				return -1;
			}
		}
		else if(nread == 0){
			break;
		}
		nleft -= nread;
		ptr += nread;
	}
	return nbytes - nleft;
}

ssize_t writen(int fd, const void * buff, size_t nbytes){
	size_t nleft = nbytes;
	ssize_t nwritten;
	const char *ptr = static_cast<char *>(const_cast<void*>(buff));

	while(nleft > 0){
		if( (nwritten = write(fd,ptr,nleft)) <=0){
			if(nwritten < 0 && errno == EINTR){
				nwritten = 0;
			}
			else{
				return -1;
			}
		}
		nleft -= nwritten;
		ptr += nwritten;
	}
	return nbytes;
}

//设计一个readline函数
ssize_t readline(int fd, void * buff, size_t maxlen){
	ssize_t i=1,rc;
	char c;
	for(i;i<maxlen;i++){
		if( (rc = read(fd, &c, 1)) == 1){
			
		}
	
	
	}
	return i;
}

ssize_t Close(int fd){
	ssize_t ret;
	if( (ret=close(fd)) < 0){
		err("close err");
	}
	return ret;
}
