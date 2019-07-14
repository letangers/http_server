#ifndef HANDLE_H
#define HANDLE_H

#include "Buffer.h"
#include <string>
#include <map>
#include "Epoll.h"
#include <memory>
#include <algorithm>

#include "data/static_data.h"

class HttpField{
	public:
		std::string method_;
		std::string uri_;
		std::string version_;
		std::string host_;
		int content_length_;
		bool keep_alive_;
		void SetInfo(){
			std::string value;
			if(GetField("Content-Length",value)){
				content_length_ = stoi(value);
			}
			else{
				content_length_ = 0;
			}
			if(GetField("Host",value)){
				host_ = value;
			}
			if(GetField("Connection",value)){
				if(value == "keep-alive"){
					keep_alive_ = true;
				}
				else{
					keep_alive_ = false;
				}
			}
		}
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
		void ShowField(){
			std::cout<<method_<<"   "<<uri_<<"   "<<version_<<std::endl;
			for(auto &one : fields_){
				std::cout<<one.first<<"  :  "<<one.second<<std::endl;
			}
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
		bool ParseFirstLine(std::string &one);
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
