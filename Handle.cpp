#include "Handle.h"

bool Handle::ParseFirstLine(std::string &one){
	int locate = one.find(" ");
	if(locate < 0){
		std::cout<<"parse first line error"<<std::endl;
		return false;
	}
	http_field_.method_.assign(std::string(one,0,locate));
	size_t f = locate + 1;
	locate = one.find(" ",f);
	if(locate < 0){
		std::cout<<"parse first line error"<<std::endl;
		return false;
	}
	http_field_.uri_.assign(std::string(one,f,locate-f));
	http_field_.version_.assign(std::string(one,locate,one.length()));

}

bool Handle::ParseReq(){
	std::vector<char> buff(65535);
	ssize_t ret = Read(connfd_,&(*buff.begin()),65535);
	if(ret <= 0){
		close(connfd_);
		return false;
	}
	//show req
	/*
	for(int i = 0;i<ret;i++){
		std::cout<<buff[i];
	}
	std::cout<<std::endl;
	*/

	std::vector<std::string> lines;
	auto line_begin = buff.begin();
	for(auto iter = buff.begin();iter != buff.begin()+ret;iter++){
		if(*line_begin == '\r'){
			//push left data to recv buf
			if(line_begin+2 != buff.end()){
				recv_buf_.Append(line_begin+2,buff.end());
			}
			break;
		}
		if(*iter == '\r'){
			if(std::distance(buff.begin(),iter) != ret-1 && *(iter+1) == '\n'){
				lines.emplace_back(line_begin,iter);
				line_begin = iter + 2;
			}
			else{
				std::cout<<"parse line error"<<std::endl;
			}
		}
	}
	for(auto &one : lines){
		int locate = one.find(": ");
		//method , uri , version
		if(locate < 0){
			ParseFirstLine(one);
			continue;
		}
		http_field_.SetField(std::string(one,0,locate),std::string(one,locate+2,one.length()));
	}
	http_field_.SetInfo();

	return true;
}

bool Handle::RecvData(){
	if(http_field_.content_length_ > recv_buf_.Size()){
		if(recv_buf_.RecvBuf(connfd_,http_field_.content_length_) < 0){
			return false;
		}
	}
	return true;
}

bool Handle::HandleReq(){

		std::string msg = "HTTP/1.1 200 OK\r\n";
		msg += "Content-type: text/html\r\n";
		msg+="\r\n<html><title>test</title><body>hello word</body></html>\r\n";
		//msg+="\r\n<html><title>test</title><link rel=\"stylesheet\" href=\"/css/default.css\" /><body>hello word</body></html>";
	send_buf_.Append(msg.begin(),msg.end());

	//if something wrong,send err msg{
	//	SendErrMsg();
	//	return false;
	//}

	recv_buf_.Clear();
	return true;
}

bool Handle::SendResponse(){
	if(send_buf_.SendBuf(connfd_) < 0){
		return false;
	}
	send_buf_.Clear();
	return true;
}

bool Handle::SendErrMsg(const std::string & err_num,
						const std::string & brief_msg,
						const std::string & err_content){

	return true;
}


int Handle::handle(){
	//if 
	if(event_->events & EPOLLRDHUP){
		Close(connfd_);
	}
	else if(event_->events & EPOLLIN){
		auto http_field_data = HttpFieldData::GetInstance();
		auto trie = http_field_data->trie_;
		//read req
		if(!ParseReq()){
			return -1;
		}
		//delete
		http_field_.ShowField();
		if(!RecvData()){
			return -1;
		}
		//delete
		recv_buf_.ShowBuf();
		if(!HandleReq()){
			return 0;
		}
		if(!SendResponse()){
			return -1;
		}
		//if keep-alive,return 1
		if(http_field_.keep_alive_){
			Close(connfd_);
			return 1;
		}
		else{
			Close(connfd_);
		}
	}
	return 0;
}

