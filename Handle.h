#ifndef HANDLE_H
#define HANDLE_H

#include "Buffer.h"
#include <string>
#include <map>
#include "Epoll.h"
#include <memory>

class HttpField{
	public:
		std::string methond_;
		std::string uri_;
		std::string version_;
		std::string host_;
		std::string user_agant_;
		bool keep_alive_;
		bool SetField(const std::string &field,const std::string &value){
			if(fields_.find(field)==fields_.end()){
				fields_[field] = value;
			}
			else{
				return false;
			}
			return true;
		}
		bool GetField(const std::string &field, std::string &value){
			if(fields_.find(field)==fields_.end()){
				return false;
			}
			value = fields_[field];
			return true;
		}
	private:
		std::map<std::string,std::string> fields_;
};

class Handle{
	private:
		Buffer recv_buf_;
		Buffer send_buf_;
		HttpField http_field_;
		int connfd_;
		std::shared_ptr<struct epoll_event> event_;
		bool ParseReq();
		bool RecvData();
		bool HandleReq();
		bool SendResponse();
		bool SendErrMsg(const std::string & err_num,
						const std::string & brief_msg,
						const std::string & err_content);

	public:
		Handle(int connfd):connfd_(connfd){}
		Handle(std::shared_ptr<struct epoll_event> event):event_(event){
			connfd_ = event_->data.fd;
			}
		~Handle(){}
		int GetConnfd(){
			return connfd_;
		}
		bool GetHttpField(const std::string &field, std::string &value){
			if(!http_field_.GetField(field,value)){
				return false;
			}
			return true;
		}

		int handle();
};

#endif
