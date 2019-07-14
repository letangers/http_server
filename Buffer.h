#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include "Io.h"

class Buffer{
	private:
		std::vector<char> buffer_;
		int head_;
		int tail_;

	public:
		Buffer():head_(-1),tail_(0){}
		~Buffer(){}
		void Clear(){
			head_ = -1;
			tail_ = 0;
			buffer_.clear();
			buffer_.shrink_to_fit();
		}
		void Append(std::vector<char>::iterator begin,std::vector<char>::iterator end){
			Resize(buffer_.size() + std::distance(begin,end));
			std::copy(begin,end,buffer_.begin());
		}
		void Append(std::string::iterator begin,std::string::iterator end){
			Resize(buffer_.size() + std::distance(begin,end));
			std::copy(begin,end,buffer_.begin());
		}

		void Resize(int size){
			buffer_.resize(size);
		}
		size_t Size(){
			return buffer_.size();
		}
		int RecvBuf(int fd, int length){
			Resize(length);
			int ret = readn(fd,&(*(buffer_.begin()+Size())),length - Size());
			return ret;
		}
		int SendBuf(int fd){
			int ret = writen(fd,&(*buffer_.begin()),Size());
			return ret;
		}
};

#endif
