#include "PerConnect.h"

//作为线程函数，线程销毁时关闭connfd
void per_connect(int connfd){
	char buff[65535];
	while(true){
		//ssize_t ret=readn(connfd,buff,65535);
		ssize_t ret=Read(connfd,buff,65535);
		if(ret<=0){
			close(connfd);
			return ;
		}
		std::cout<<buff<<std::endl;
		//parse request and then do different operation
		std::string msg = "HTTP/1.1 200 OK\r\n";
		msg += "Content-type: text/html\r\n";
		msg+="\r\n<html><title>test</title><body>hello word</body></html>\r\n";
		//msg+="\r\n<html><title>test</title><link rel=\"stylesheet\" href=\"/css/default.css\" /><body>hello word</body></html>";
		if(ret>0){
			ret=writen(connfd,msg.c_str(),msg.length());
			//ret=write(connfd,msg.c_str(),msg.length());
			Close(connfd);
			return ;
		}
	}
}
